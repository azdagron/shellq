#include "precomp.h"

#include "ClassFactory.h"
#include "ContextMenu.h"

namespace {
  HINSTANCE g_instance;
  ULONG g_ref;
}

HINSTANCE DllInstance() {
  return g_instance;
}

void AddGlobalRef() {
  InterlockedIncrement(&g_ref);
}

void ReleaseGlobalRef() {
  InterlockedDecrement(&g_ref);
}

ULONG GetGlobalRef() {
  return InterlockedCompareExchange(&g_ref, 0, 0);
}

BOOL WINAPI DllMain(
  _In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved
)
{
  g_instance = hinstDLL;
  return TRUE;
}

STDAPI DllGetClassObject(
  REFCLSID clsid,
  REFIID   riid,
  LPVOID   *ppv
) {
  if (clsid == __uuidof(ContextMenu)) {
    return ClassFactory<ContextMenu>::New(riid, ppv);
  }
  return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow() {
  return GetGlobalRef() ? S_FALSE : S_OK;
}
