

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Sep 21 22:01:57 2016
 */
/* Compiler settings for shellq.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __shellq_h__
#define __shellq_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFileOperationQueue_FWD_DEFINED__
#define __IFileOperationQueue_FWD_DEFINED__
typedef interface IFileOperationQueue IFileOperationQueue;

#endif 	/* __IFileOperationQueue_FWD_DEFINED__ */


#ifndef __ContextMenu_FWD_DEFINED__
#define __ContextMenu_FWD_DEFINED__

#ifdef __cplusplus
typedef class ContextMenu ContextMenu;
#else
typedef struct ContextMenu ContextMenu;
#endif /* __cplusplus */

#endif 	/* __ContextMenu_FWD_DEFINED__ */


#ifndef __FileOperationQueue_FWD_DEFINED__
#define __FileOperationQueue_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileOperationQueue FileOperationQueue;
#else
typedef struct FileOperationQueue FileOperationQueue;
#endif /* __cplusplus */

#endif 	/* __FileOperationQueue_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFileOperationQueue_INTERFACE_DEFINED__
#define __IFileOperationQueue_INTERFACE_DEFINED__

/* interface IFileOperationQueue */
/* [uuid][object] */ 


EXTERN_C const IID IID_IFileOperationQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c2201419-8d7e-4894-b9e5-0b1da12aa5ff")
    IFileOperationQueue : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MoveItems( 
            /* [in] */ IUnknown *items,
            /* [in] */ IShellItem *dest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyItems( 
            /* [in] */ IUnknown *items,
            /* [in] */ IShellItem *dest) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFileOperationQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileOperationQueue * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileOperationQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileOperationQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *MoveItems )( 
            IFileOperationQueue * This,
            /* [in] */ IUnknown *items,
            /* [in] */ IShellItem *dest);
        
        HRESULT ( STDMETHODCALLTYPE *CopyItems )( 
            IFileOperationQueue * This,
            /* [in] */ IUnknown *items,
            /* [in] */ IShellItem *dest);
        
        END_INTERFACE
    } IFileOperationQueueVtbl;

    interface IFileOperationQueue
    {
        CONST_VTBL struct IFileOperationQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileOperationQueue_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileOperationQueue_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileOperationQueue_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileOperationQueue_MoveItems(This,items,dest)	\
    ( (This)->lpVtbl -> MoveItems(This,items,dest) ) 

#define IFileOperationQueue_CopyItems(This,items,dest)	\
    ( (This)->lpVtbl -> CopyItems(This,items,dest) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileOperationQueue_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


