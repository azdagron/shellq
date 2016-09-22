#include "precomp.h"

namespace  {
    CLSID TrayGuid = { /* 9cd9214d-853f-4ea3-938d-63e45973cb4f */
        0x9cd9214d,
        0x853f,
        0x4ea3,
        {0x93, 0x8d, 0x63, 0xe4, 0x59, 0x73, 0xcb, 0x4f}
      };
}

void AddTrayIcon(HWND hwnd) {
    NOTIFYICONDATA nid;
    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.uFlags = NIF_ICON | NIF_TIP;
    nid.guidItem = TrayGuid;
    nid.hWnd = hwnd;

    HRESULT hr = LoadIconMetric(DllInstance(),
        MAKEINTRESOURCE(IDI_TRAY_ICON), LIM_SMALL, &nid.hIcon);
    if (FAILED(hr)) {
        Alart(hr, L"LoadIconMetric");
    }
    StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"ShellQ: no jobs pending");

    if (!Shell_NotifyIcon(NIM_ADD, &nid)) {
        Alart(HRESULT_FROM_WIN32(GetLastError()), L"NotifyIcon");
    }
    //if (nid.hIcon) {
    //    ::DestroyIcon(nid.hIcon);
    //}
}
