#pragma once

#include <shlobj.h>

class OperationQueue : public IOperationQueue {
public:
  static HRESULT New(REFIID riid, void** ppv);

  STDMETHOD_(ULONG, AddRef)();
  STDMETHOD_(ULONG, Release)();
  STDMETHOD(QueryInterface)(REFIID iid, void **ppv);

  // IOperationQueue interface
  STDMETHOD(MoveItems)(
    IUnknown* items,
    IShellItem* dest
    );

  STDMETHOD(CopyItems)(
    IUnknown* items,
    IShellItem* dest
    );

private:
  OperationQueue();
  ~OperationQueue();

private:
  ULONG ref_;
};
