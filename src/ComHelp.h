#pragma once

template <typename T>
class ComPtr {
public:
  ComPtr() : t_(nullptr) {}

  ComPtr(T* t) : t_(nullptr) {
    Attach(t);
  }
  ~ComPtr() {
    Attach(nullptr);
  }

  T** operator&() {
    return &t_;
  }

  operator T*() {
    return t_;
  }

  ComPtr& operator=(T *t) {
    Attach(t);
    return *this;
  }

  T* operator->() {
    return t_;
  }

  void Attach(T* t) {
    if (t_) {
      t_->Release();
    }
    t_ = t;
  }
private:
 T* t_;
};

template <typename T>
class CoTaskMem {
public:
  CoTaskMem() : t_(nullptr) {}

  CoTaskMem(T* t) : t_(nullptr) {
    Attach(t);
  }
  ~CoTaskMem() {
    Attach(nullptr);
  }

  T** operator&() {
    return &t_;
  }

  operator T*() {
    return t_;
  }

  CoTaskMem& operator=(T *t) {
    Attach(t);
    return *this;
  }

  T* operator->() {
    return t_;
  }

  void Attach(T* t) {
    if (t_) {
      CoTaskMemFree(t);
    }
    t_ = t;
  }
private:
 T* t_;
};

template <typename T>
class ClassFactory : public IClassFactory {
public:
  ClassFactory() : ref_(0) {}

  static HRESULT New(REFIID riid, void** ppv) {
    ClassFactory* obj = new (std::nothrow) ClassFactory();
    if (!obj) {
      return E_OUTOFMEMORY;
    }
    obj->AddRef();
    HRESULT hr = obj->QueryInterface(riid, ppv);
    obj->Release();
    return S_OK;
  }

  // IUnknown interface
  STDMETHODIMP_(ULONG) AddRef() {
    return InterlockedIncrement(&ref_);
  }
  STDMETHODIMP_(ULONG) Release() {
    ULONG ref = InterlockedDecrement(&ref_);
    if (ref == 0) {
      delete this;
    }
    return ref;
  }

  STDMETHODIMP QueryInterface(REFIID iid, void **ppv) {
    static const QITAB rgqit[] {   
        QITABENT(ClassFactory, IClassFactory),
        { 0 },
    };
    return QISearch(this, rgqit, iid, ppv);
  }

  // IClassFactory interface
  STDMETHODIMP CreateInstance(
    IUnknown *outer,
    REFIID   riid,
    void     **ppv
  ) {
    return T::New(riid, ppv);
  }
  
  HRESULT LockServer(BOOL lock) {
    if (lock) {
      AddGlobalRef();
    } else {
      ReleaseGlobalRef();
    }
    return S_OK;
  }

private:
  ULONG ref_;
};

