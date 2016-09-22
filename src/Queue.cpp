#include "precomp.h"

#include "Queue.h"
#include "TrayIcon.h"

#include <memory>
#include <list>

namespace {
    struct Entry {
        OperationKind kind;
        ComPtr<IUnknown> items;
        ComPtr<IShellItem> dest;

        Entry() {}
        Entry(OperationKind akind, IUnknown* aitems, IShellItem* adest)
            : kind(akind), items(aitems), dest(adest) {}
    };

    SRWLOCK entriesLock = SRWLOCK_INIT;
    std::list<std::shared_ptr<Entry>> entries;

    HRESULT RunOperation(OperationKind kind, IUnknown* items, IShellItem* dest) {
        ComPtr<IFileOperation> op;
        HRESULT hr = ::CoCreateInstance(CLSID_FileOperation, NULL,
            CLSCTX_ALL, IID_PPV_ARGS(&op));
        if (FAILED(hr)) {
            Alart(hr, L"Create file operation");
            return hr;
        }

        switch (kind) {
        case OperationKind::Move:
            hr = op->MoveItems(items, dest);
            break;
        case OperationKind::Copy:
            hr = op->CopyItems(items, dest);
            break;
        }
        if (FAILED(hr)) {
            Alart(hr, L"add items");
            return hr;
        }

        hr = op->PerformOperations();
        if (FAILED(hr)) {
            Alart(hr, L"perform operations");
            return hr;
        }
        return hr;
    }

    HWND queueHwnd = nullptr;
}

LRESULT CALLBACK QueueWndProc(
  _In_ HWND   hwnd,
  _In_ UINT   msg,
  _In_ WPARAM wparam,
  _In_ LPARAM lparam
) {
    switch (msg) {
        case WM_TIMER:
            break;
    }
    return ::DefWindowProc(hwnd, msg, wparam, lparam);
}


void CreateQueueWindow() {
    if (queueHwnd) {
        return;
    }

    WNDCLASSEX clazz;
    ZeroMemory(&clazz, sizeof(clazz));
    clazz.cbSize = sizeof(WNDCLASSEX);
    clazz.lpfnWndProc = QueueWndProc;
    clazz.hInstance = DllInstance();
    clazz.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    clazz.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    clazz.lpszClassName= L"ShellQ Queue Window";

    ::RegisterClassEx(&clazz);

    HWND hwnd = ::CreateWindowEx(WS_EX_CLIENTEDGE, clazz.lpszClassName,
            L"ShellQ", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            400, 200, NULL, NULL, DllInstance(), NULL);
    ::ShowWindow(hwnd, SW_SHOW);
    ::UpdateWindow(hwnd);
    ::SetTimer(hwnd, 0, 500, NULL);

    WCHAR ouchy[256];
    StringCchPrintf(ouchy, ARRAYSIZE(ouchy), L"PID: %d", GetCurrentProcessId());
    ::SetWindowText(hwnd, ouchy);
    queueHwnd = hwnd;

    AddTrayIcon(hwnd);
}

HRESULT AddOperation(OperationKind kind, IUnknown* items, IShellItem* dest) {
    AcquireSRWLockExclusive(&entriesLock);
    entries.push_back(std::make_shared<Entry>(kind, items, dest));
    ReleaseSRWLockExclusive(&entriesLock);
    return S_OK;
}
