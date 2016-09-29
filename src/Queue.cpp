#include "precomp.h"

#include "Queue.h"
#include "TrayIcon.h"

#include <memory>
#include <list>

namespace {
    UINT WM_QUEUE_CHANGED = ::RegisterWindowMessageW(L"ShellQ.QueueChanged");

    struct Entry {
        OperationKind kind;
        ComPtr<IUnknown> items;
        ComPtr<IShellItem> dest;

        Entry() {}
        Entry(OperationKind akind, IUnknown* aitems, IShellItem* adest)
            : kind(akind), items(aitems), dest(adest) {}
    };

	HWND queueHwnd = nullptr;
	HWND logHwnd = nullptr;
	std::list<std::shared_ptr<Entry>> queueEntries;
	bool inProcess = false;

	void appendText(HWND hwnd, PCWSTR fmt, ...) {
		WCHAR msg[1024];

		va_list ap;
		va_start(ap, fmt);
		vswprintf_s(msg, fmt, ap);
		va_end(ap);

		int length = ::GetWindowTextLength(hwnd);

		DWORD start;
		DWORD end;
		::SendMessage(hwnd, EM_GETSEL, reinterpret_cast<WPARAM>(&start), reinterpret_cast<LPARAM>(&end));
		::SendMessage(hwnd, EM_SETSEL, length, length);
		::SendMessage(hwnd, EM_REPLACESEL, TRUE, reinterpret_cast<LPARAM>(msg));
		::SendMessage(hwnd, EM_SETSEL, start, end);
	}

	void logError(HRESULT hr, PCWSTR title) {
		appendText(logHwnd, L"%ws failed (hr=%08x)\n", title, hr);
	}


    

	
}

LRESULT CALLBACK QueueWndProc(
  _In_ HWND   hwnd,
  _In_ UINT   msg,
  _In_ WPARAM wparam,
  _In_ LPARAM lparam
) {
    if (msg == WM_QUEUE_CHANGED) {
        ::SetWindowText(logHwnd, L"");
        for (auto const& entry : queueEntries) {
            appendText(logHwnd, L"entry");
        }
        // Update visuals
        return 0;    
    }

    if (msg == WM_SIZE) {
        RECT rc;
        ::GetClientRect(hwnd, &rc);
        ::SetWindowPos(logHwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
    }
    return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

void CreateQueueWindow() {
    if (queueHwnd) {
        return;
    }


    LOGFONT lf;
    ::ZeroMemory(&lf, sizeof(lf));
    HDC hdc = ::GetDC(NULL);
    lf.lfHeight = -::MulDiv(12, ::GetDeviceCaps(hdc, LOGPIXELSY), 72);
    ::ReleaseDC(NULL, hdc);
    lf.lfQuality = CLEARTYPE_QUALITY;
    lf.lfPitchAndFamily = FF_MODERN | FIXED_PITCH;
    HFONT font = ::CreateFontIndirect(&lf);

    WNDCLASSEX clazz;
    ::ZeroMemory(&clazz, sizeof(clazz));
    clazz.cbSize = sizeof(WNDCLASSEX);
    clazz.lpfnWndProc = QueueWndProc;
    clazz.hInstance = DllInstance();
    clazz.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    clazz.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    clazz.lpszClassName= L"ShellQ Queue Window";

    ::RegisterClassEx(&clazz);

    HWND hwnd = ::CreateWindowExW(WS_EX_CLIENTEDGE, clazz.lpszClassName,
            L"ShellQ", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            460, 400, NULL, NULL, DllInstance(), NULL);

	RECT rc;
	::GetClientRect(hwnd, &rc);
	logHwnd = ::CreateWindowExW(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_READONLY, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hwnd, NULL, DllInstance(), NULL);
    ::SendMessage(logHwnd, WM_SETFONT, reinterpret_cast<WPARAM>(font), TRUE);

    ::ShowWindow(hwnd, SW_SHOW);
    ::UpdateWindow(hwnd);

	appendText(hwnd, L"SHELLQ LOG: PID=%d", GetCurrentProcessId());
    queueHwnd = hwnd;
    AddTrayIcon(hwnd);
}

HRESULT RunOperation(OperationKind kind, IUnknown* items, IShellItem* dest) {
    ComPtr<IFileOperation> op;
    HRESULT hr = op.CreateInstance(CLSID_FileOperation, CLSCTX_ALL);
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


HRESULT AddOperation(OperationKind kind, IUnknown* items, IShellItem* dest) {
    CreateQueueWindow();
    queueEntries.push_back(std::make_shared<Entry>(kind, items, dest));
    ::PostMessage(queueHwnd, WM_QUEUE_CHANGED, 0, 0);

    if (inProcess) {
        return 0;
    }
    inProcess = true;
    for (auto it = queueEntries.begin(); it != queueEntries.end(); ) {
        auto entry = queueEntries.front();
        RunOperation(entry->kind, entry->items, entry->dest);
        // TODO: result?
        it = queueEntries.erase(it);
        ::PostMessage(queueHwnd, WM_QUEUE_CHANGED, 0, 0);
    }
    inProcess = false;

    return S_OK;
}
