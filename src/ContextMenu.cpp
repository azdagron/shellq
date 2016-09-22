#include "precomp.h"

#include "ContextMenu.h"

namespace {
  enum Command : UINT {
    QueueMoveCmd = 1,
    QueueCopyCmd = 2,
    LastCmd
  };
}

ContextMenu::ContextMenu()
  : ref_(0) {
  AddGlobalRef();
}

ContextMenu::~ContextMenu() {
  folder_ = nullptr;
  obj_ = nullptr;
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
    };

    return QISearch(this, rgqit, iid, ppv);
}

STDMETHODIMP ContextMenu::Initialize(
    PCIDLIST_ABSOLUTE folder_pidl,
    IDataObject       *data_object,
    HKEY              prog_id
  ) {
  HRESULT hr = SHCreateItemFromIDList(folder_pidl, IID_PPV_ARGS(&folder_));
  if (FAILED(hr)) {
    return hr;
  }


  obj_ = data_object;
  obj_->AddRef();
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

void Alart(HRESULT hr, LPCWSTR title) {
    WCHAR err[256];
    swprintf_s(err, ARRAYSIZE(err), L"0x%08x", hr);
    MessageBoxW(NULL, err, title, MB_OK);
}

STDMETHODIMP ContextMenu::InvokeCommand(
   LPCMINVOKECOMMANDINFO info
) {
  ComPtr<IFileOperation> op;
  HRESULT hr = CoCreateInstance(CLSID_FileOperation, NULL, CLSCTX_ALL,
    IID_PPV_ARGS(&op));
  if (FAILED(hr)) {
    MessageBoxW(NULL, L"NOOO", L"OPCREATE", MB_OK);
    return hr;
  }

  switch (LOWORD(info->lpVerb)) {
    case QueueMoveCmd:
      hr = op->MoveItems(obj_, folder_);
      break;
    case QueueCopyCmd:
      hr = op->CopyItems(obj_, folder_);
      break;
    default:
      return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
  }
  if (FAILED(hr)) {
    MessageBoxW(NULL, L"NOOO", L"SETOPT", MB_OK);
    return hr;
  }

  hr = op->PerformOperations();
  if (FAILED(hr)) {
    Alart(hr, L"PERFORM");
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
