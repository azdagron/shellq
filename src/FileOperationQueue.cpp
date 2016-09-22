#include "precomp.h"

#include "FileOperationQueue.h"
#include "TrayIcon.h"
#include "Queue.h"

FileOperationQueue::FileOperationQueue()
  : ref_(0) {
    AddGlobalRef();
}

FileOperationQueue::~FileOperationQueue() {
    ReleaseGlobalRef();
}

HRESULT FileOperationQueue::New(REFIID riid, void** ppv) {
    FileOperationQueue* obj = new (std::nothrow) FileOperationQueue();
    if (!obj) {
        return E_OUTOFMEMORY;
    }
    obj->AddRef();
    HRESULT hr = obj->QueryInterface(riid, ppv);
    obj->Release();
    return hr;
}

STDMETHODIMP_(ULONG) FileOperationQueue::AddRef() {
    return InterlockedIncrement(&ref_);
}

STDMETHODIMP_(ULONG) FileOperationQueue::Release() {
    ULONG ref = InterlockedDecrement(&ref_);
    if (ref == 0) {
        delete this;
    }
    return ref;
}

STDMETHODIMP FileOperationQueue::QueryInterface(REFIID iid, void **ppv) {
    static const QITAB rgqit[] {   
        QITABENT(FileOperationQueue, IFileOperationQueue),
        { 0 },
    };

    return QISearch(this, rgqit, iid, ppv);
}

STDMETHODIMP FileOperationQueue::MoveItems(IUnknown* items, IShellItem* dest) {
    return AddOperation(OperationKind::Move, items, dest);
}

STDMETHODIMP FileOperationQueue::CopyItems( IUnknown* items, IShellItem* dest) {
    return AddOperation(OperationKind::Copy, items, dest);
}
