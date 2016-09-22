#include "precomp.h"

#include "ContextMenu.h"
#include "FileOperationQueue.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace {
    HINSTANCE dllInstance;
    ULONG globalRef;
}

HINSTANCE DllInstance() {
    return dllInstance;
}

void AddGlobalRef() {
    InterlockedIncrement(&globalRef);
}

void ReleaseGlobalRef() {
    InterlockedDecrement(&globalRef);
}

ULONG GetGlobalRef() {
    return InterlockedCompareExchange(&globalRef, 0, 0);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        dllInstance = instance;
        ::DisableThreadLibraryCalls(instance);
    }
    return TRUE;
}

// Proxy implementations
STDAPI ProxyDllGetClassObject(REFCLSID clsid, REFIID riid, LPVOID *ppv);
STDAPI ProxyDllCanUnloadNow();

STDAPI DllGetClassObject(REFCLSID clsid, REFIID riid, LPVOID *ppv) {
    if (IsEqualCLSID(clsid, CLSID_ContextMenu)) {
        return ClassFactory<ContextMenu>::New(riid, ppv);
    }
    if (IsEqualCLSID(clsid, CLSID_FileOperationQueue)) {
        return ClassFactory<FileOperationQueue>::New(riid, ppv);
    }
    return ProxyDllGetClassObject(clsid, riid, ppv);
}

STDAPI DllCanUnloadNow() {
    if (GetGlobalRef()) {
        return S_FALSE;
    }
    return ProxyDllCanUnloadNow();
}
