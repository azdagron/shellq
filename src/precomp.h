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

#include <windows.h>
#include <shobjidl.h>
#include <shlwapi.h>

#include <new>
#include <cstdio>

#include "resource.h"

HINSTANCE DllInstance();

void AddGlobalRef();
void ReleaseGlobalRef();
ULONG GetGlobalRef();

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
