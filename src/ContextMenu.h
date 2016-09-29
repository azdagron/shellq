#pragma once

class ContextMenu : public IShellExtInit,
                    public IContextMenu {
public:
  static HRESULT New(REFIID riid, void** ppv);

  STDMETHOD_(ULONG, AddRef)();
  STDMETHOD_(ULONG, Release)();
  STDMETHOD(QueryInterface)(REFIID iid, void **ppv);

  // IShellExtInit interface
  STDMETHOD(Initialize)(
    PCIDLIST_ABSOLUTE folder_pidl,
    IDataObject       *data_object,
    HKEY              prog_id
  );

  // IContextMenu interface
  STDMETHOD(GetCommandString)(
     UINT_PTR cmd,
     UINT     flags,
     UINT     *reserved,
     LPSTR    name,
     UINT     max_name_len
  );

  STDMETHOD(InvokeCommand)(
     LPCMINVOKECOMMANDINFO info
  );
  
  STDMETHOD(QueryContextMenu)(
     HMENU menu,
     UINT  menu_idx,
     UINT  first_cmd,
     UINT  last_cmd,
     UINT  flags
  );

private:
  ContextMenu();
  ~ContextMenu();

private:
  ULONG ref_;
  ComPtr<IShellItem> dest_;
  ComPtr<IDataObject> items_;
};
