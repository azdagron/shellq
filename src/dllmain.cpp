#include "precomp.h"

#include "ContextMenu.h"
#include "OperationQueue.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


CLSID CLSID_OurProxyFactory = {
	0xbc4fb9a5,
	0x2814,
	0x42fe,
	{0xa2, 0x69, 0x64, 0x21, 0x87, 0xb2, 0x14, 0x6c}
};

namespace {
	HINSTANCE dllInstance = 0;
	ULONG globalRef = 0;
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
	if (IsEqualCLSID(clsid, CLSID_OperationQueue)) {
		return ClassFactory<OperationQueue>::New(riid, ppv);
	}
	return ProxyDllGetClassObject(clsid, riid, ppv);
}

STDAPI DllCanUnloadNow() {
	HRESULT hr = S_OK;
	if (GetGlobalRef()) {
		hr = S_FALSE;
	}
	if (hr == S_OK) {
		hr = ProxyDllCanUnloadNow();
	}
	if (hr == S_OK) {
		Debug(L"PID: %d: DllCanUnloadNow returning true", GetCurrentProcessId());
    }
    return hr;
}
