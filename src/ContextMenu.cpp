#include "precomp.h"

#include "ContextMenu.h"

#include <memory>

namespace {
    enum Command : UINT {
        QueueMoveCmd = 1,
        QueueCopyCmd = 2,
        LastCmd
    };

    struct InvokeCommandParams {
        Command cmd;
        ComPtr<IStream> items;
        ComPtr<IStream> dest;
    };

    HRESULT InvokeCommand(InvokeCommandParams* params) {
        // Unmarshal the stuff
        ComPtr<IDataObject> items;
        ComPtr<IShellItem> dest;

        HRESULT hr = S_OK;
        
        hr = CoUnmarshalInterface(params->items, IID_PPV_ARGS(&items));
        if (FAILED(hr)) {
            Alart(hr, L"Cannot unmarshal items");
            return hr;
        }

        hr = CoUnmarshalInterface(params->dest, IID_PPV_ARGS(&dest));
        if (FAILED(hr)) {
            Alart(hr, L"Cannot unmarshal dest");
            return hr;
        }

        ComPtr<IOperationQueue> op;
        hr = CoCreateInstance(CLSID_OperationQueue, NULL,
                CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&op));
        if (FAILED(hr)) {
            Alart(hr, L"Cannot instantiate file operation queue");
            return hr;
        }

        switch (params->cmd) {
            case QueueMoveCmd:
                hr = op->MoveItems(items, dest);
                break;
            case QueueCopyCmd:
                hr = op->CopyItems(items, dest);
                break;
        }
        if (FAILED(hr)) {
            Alart(hr, L"InvokeCommand");
            return hr;
        }

        return S_OK;
    }

    DWORD WINAPI ThreadProc(LPVOID lpParameter) {
        std::unique_ptr<InvokeCommandParams> params(
                static_cast<InvokeCommandParams*>(lpParameter));
        return static_cast<DWORD>(InvokeCommand(params.get()));
    }
}

ContextMenu::ContextMenu()
  : ref_(0) {
    AddGlobalRef();
}

ContextMenu::~ContextMenu() {
    dest_ = nullptr;
    items_ = nullptr;
    ReleaseGlobalRef();
}

HRESULT ContextMenu::New(REFIID riid, void** ppv) {
    ContextMenu* obj = new (std::nothrow) ContextMenu();
    if (!obj) {
        return E_OUTOFMEMORY;
    }
    obj->AddRef();
    HRESULT hr = obj->QueryInterface(riid, ppv);
    obj->Release();
    return hr;
}

STDMETHODIMP_(ULONG) ContextMenu::AddRef() {
    return InterlockedIncrement(&ref_);
}

STDMETHODIMP_(ULONG) ContextMenu::Release() {
    ULONG ref = InterlockedDecrement(&ref_);
    if (ref == 0) {
        delete this;
    }
    return ref;
}

STDMETHODIMP ContextMenu::QueryInterface(REFIID iid, void **ppv) {
    static const QITAB rgqit[] {   
        QITABENT(ContextMenu, IShellExtInit),
        QITABENT(ContextMenu, IContextMenu),
        { 0 },
// Geez. Can't build cleanly w/ it's own stuff APIs
#pragma warning( push )
#pragma warning( disable: 4365 )
#pragma warning( disable: 4838 )
    }
#pragma warning( pop )
    ;
    return QISearch(this, rgqit, iid, ppv);
}

STDMETHODIMP ContextMenu::Initialize(
        PCIDLIST_ABSOLUTE folder_pidl,
        IDataObject       *data_object,
        HKEY              prog_id
        ) {

    HRESULT hr = SHCreateItemFromIDList(folder_pidl, IID_PPV_ARGS(&dest_));
    if (FAILED(hr)) {
        return hr;
    }
    items_ = data_object;
    items_->AddRef();
    return S_OK;
}

STDMETHODIMP ContextMenu::GetCommandString(
        UINT_PTR cmd,
        UINT     flags,
        UINT     *reserved,
        LPSTR    name,
        UINT     max_name_len
        ) {
    return E_NOTIMPL;
}

STDMETHODIMP ContextMenu::InvokeCommand(
        LPCMINVOKECOMMANDINFO info
        ) {
    std::unique_ptr<InvokeCommandParams> params(new InvokeCommandParams);
    params->cmd = static_cast<Command>(LOWORD(info->lpVerb));

    HRESULT hr = S_OK;

    hr = CoMarshalInterThreadInterfaceInStream(IID_IDataObject, items_,
            &params->items);
    if (FAILED(hr)) {
        Alart(hr, L"Marshal items");
        return hr;
    }

    hr = CoMarshalInterThreadInterfaceInStream(IID_IShellItem, dest_,
            &params->dest);
    if (FAILED(hr)) {
        Alart(hr, L"Marshal dest");
        return hr;
    }

    if (SHCreateThread(
            ThreadProc,
            params.get(),
            CTF_PROCESS_REF,
            NULL)) {
        params.release();
    } else {
        hr = HRESULT_FROM_WIN32(GetLastError());
        Alart(hr, L"Create InvokeCommand thread");
        return hr;
    }

    return S_OK;
}

STDMETHODIMP ContextMenu::QueryContextMenu(
        HMENU hmenu,
        UINT  menu_idx,
        UINT  first_cmd,
        UINT  last_cmd,
        UINT  flags
        ) {
    if (flags & CMF_DEFAULTONLY) {
        return S_OK;
    }

    WCHAR text[128];
    MENUITEMINFO item;
    ZeroMemory(&item, sizeof(item));
    item.cbSize = sizeof(item);
    item.fMask = MIIM_STRING | MIIM_ID | MIIM_STATE;
    item.fState = MFS_ENABLED;
    item.dwTypeData = text;

    if (!LoadString(DllInstance(), IDS_QUEUE_MOVE_CMD, text, ARRAYSIZE(text))) {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    item.wID = first_cmd + QueueMoveCmd;
    if (!InsertMenuItem(hmenu, menu_idx, TRUE, &item)) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (!LoadString(DllInstance(), IDS_QUEUE_COPY_CMD, text, ARRAYSIZE(text))) {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    item.wID = first_cmd + QueueCopyCmd;
    if (!InsertMenuItem(hmenu, menu_idx, TRUE, &item)) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return MAKE_HRESULT(SEVERITY_SUCCESS, 0, LastCmd);
}
