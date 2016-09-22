#pragma once

#include <shlobj.h>

class FileOperationQueue : public IFileOperationQueue {
public:
  static HRESULT New(REFIID riid, void** ppv);

  STDMETHOD_(ULONG, AddRef)();
  STDMETHOD_(ULONG, Release)();
  STDMETHOD(QueryInterface)(REFIID iid, void **ppv);

  // IFileOperationQueue interface
  STDMETHOD(MoveItems)(
    IUnknown* items,
    IShellItem* dest
    );

  STDMETHOD(CopyItems)(
    IUnknown* items,
    IShellItem* dest
    );

private:
  FileOperationQueue();
  ~FileOperationQueue();

private:
  ULONG ref_;
};
