#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _WINDLL
#define _WINDLL
#endif

#ifndef STRICT
#define STRICT
#endif

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#define NTDDI_VERSION NTDDI_WIN7

#include <windows.h>
#include <guiddef.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <shellapi.h>
#include <strsafe.h>

#include <new>
#include <cstdio>

#include "resource.h"
#include "shellq.h"
#include "comhelp.h"

HINSTANCE DllInstance();

void AddGlobalRef();
void ReleaseGlobalRef();
ULONG GetGlobalRef();

EXTERN_C CLSID CLSID_ContextMenu;
EXTERN_C CLSID CLSID_OperationQueue;
EXTERN_C CLSID CLSID_OurProxyFactory;

inline void Alart(HRESULT hr, LPCWSTR title) {
    WCHAR err[256];
    swprintf_s(err, ARRAYSIZE(err), L"0x%08x", hr);
    ::MessageBoxW(NULL, err, title, MB_OK);
}

inline void Debug(LPCWSTR fmt, ...) {
    WCHAR msg[256];
    va_list ap;
    va_start(ap, fmt);
    vswprintf_s(msg, fmt, ap);
    va_end(ap);
    ::MessageBoxW(NULL, msg, L"Debug", MB_OK);
}
