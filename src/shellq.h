

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Sep 28 18:53:26 2016
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

#ifndef __IOperationQueue_FWD_DEFINED__
#define __IOperationQueue_FWD_DEFINED__
typedef interface IOperationQueue IOperationQueue;

#endif 	/* __IOperationQueue_FWD_DEFINED__ */


#ifndef __ContextMenu_FWD_DEFINED__
#define __ContextMenu_FWD_DEFINED__

#ifdef __cplusplus
typedef class ContextMenu ContextMenu;
#else
typedef struct ContextMenu ContextMenu;
#endif /* __cplusplus */

#endif 	/* __ContextMenu_FWD_DEFINED__ */


#ifndef __OperationQueue_FWD_DEFINED__
#define __OperationQueue_FWD_DEFINED__

#ifdef __cplusplus
typedef class OperationQueue OperationQueue;
#else
typedef struct OperationQueue OperationQueue;
#endif /* __cplusplus */

#endif 	/* __OperationQueue_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IOperationQueue_INTERFACE_DEFINED__
#define __IOperationQueue_INTERFACE_DEFINED__

/* interface IOperationQueue */
/* [uuid][object] */ 


EXTERN_C const IID IID_IOperationQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c2201419-8d7e-4894-b9e5-0b1da12aa5ff")
    IOperationQueue : public IUnknown
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

    typedef struct IOperationQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOperationQueue * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOperationQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOperationQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *MoveItems )( 
            IOperationQueue * This,
            /* [in] */ IUnknown *items,
            /* [in] */ IShellItem *dest);
        
        HRESULT ( STDMETHODCALLTYPE *CopyItems )( 
            IOperationQueue * This,
            /* [in] */ IUnknown *items,
            /* [in] */ IShellItem *dest);
        
        END_INTERFACE
    } IOperationQueueVtbl;

    interface IOperationQueue
    {
        CONST_VTBL struct IOperationQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOperationQueue_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOperationQueue_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOperationQueue_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOperationQueue_MoveItems(This,items,dest)	\
    ( (This)->lpVtbl -> MoveItems(This,items,dest) ) 

#define IOperationQueue_CopyItems(This,items,dest)	\
    ( (This)->lpVtbl -> CopyItems(This,items,dest) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOperationQueue_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


