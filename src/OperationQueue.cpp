#include "precomp.h"

#include "OperationQueue.h"
#include "TrayIcon.h"
#include "Queue.h"

OperationQueue::OperationQueue()
  : ref_(0) {
    AddGlobalRef();
}

OperationQueue::~OperationQueue() {
    ReleaseGlobalRef();
}

HRESULT OperationQueue::New(REFIID riid, void** ppv) {
    OperationQueue* obj = new (std::nothrow) OperationQueue();
    if (!obj) {
        return E_OUTOFMEMORY;
    }
    obj->AddRef();
    HRESULT hr = obj->QueryInterface(riid, ppv);
    obj->Release();
    return hr;
}

STDMETHODIMP_(ULONG) OperationQueue::AddRef() {
    return InterlockedIncrement(&ref_);
}

STDMETHODIMP_(ULONG) OperationQueue::Release() {
    ULONG ref = InterlockedDecrement(&ref_);
    if (ref == 0) {
        delete this;
    }
    return ref;
}

STDMETHODIMP OperationQueue::QueryInterface(REFIID iid, void **ppv) {
    static const QITAB rgqit[] {   
        QITABENT(OperationQueue, IOperationQueue),
        { 0 },
// Geez. Can't build cleanly w/ it's own stuff APIs
#pragma warning( push )
#pragma warning( disable: 4365 )
#pragma warning( disable: 4838 )
    }
#pragma warning( pop )
;

    return QISearch(this, rgqit, iid, ppv);
}

STDMETHODIMP OperationQueue::MoveItems(IUnknown* items, IShellItem* dest) {
    return AddOperation(OperationKind::Move, items, dest);
}

STDMETHODIMP OperationQueue::CopyItems(IUnknown* items, IShellItem* dest) {
    AddRef();
    return AddOperation(OperationKind::Copy, items, dest);
}
