

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "shellq.h"

#define TYPE_FORMAT_STRING_SIZE   39                                
#define PROC_FORMAT_STRING_SIZE   89                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _shellq_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } shellq_MIDL_TYPE_FORMAT_STRING;

typedef struct _shellq_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } shellq_MIDL_PROC_FORMAT_STRING;

typedef struct _shellq_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } shellq_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const shellq_MIDL_TYPE_FORMAT_STRING shellq__MIDL_TypeFormatString;
extern const shellq_MIDL_PROC_FORMAT_STRING shellq__MIDL_ProcFormatString;
extern const shellq_MIDL_EXPR_FORMAT_STRING shellq__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IOperationQueue_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IOperationQueue_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const shellq_MIDL_PROC_FORMAT_STRING shellq__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure MoveItems */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter items */

/* 26 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 28 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter dest */

/* 32 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 34 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 36 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */

	/* Return value */

/* 38 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 40 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 42 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CopyItems */

/* 44 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 46 */	NdrFcLong( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x4 ),	/* 4 */
/* 52 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x8 ),	/* 8 */
/* 58 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 60 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter items */

/* 70 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 72 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 74 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter dest */

/* 76 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 78 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 80 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */

	/* Return value */

/* 82 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 84 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 86 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const shellq_MIDL_TYPE_FORMAT_STRING shellq__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/*  4 */	NdrFcLong( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x0 ),	/* 0 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 14 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 16 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 18 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 20 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 22 */	NdrFcLong( 0x43826d1e ),	/* 1132621086 */
/* 26 */	NdrFcShort( 0xe718 ),	/* -6376 */
/* 28 */	NdrFcShort( 0x42ee ),	/* 17134 */
/* 30 */	0xbc,		/* 188 */
			0x55,		/* 85 */
/* 32 */	0xa1,		/* 161 */
			0xe2,		/* 226 */
/* 34 */	0x61,		/* 97 */
			0xc3,		/* 195 */
/* 36 */	0x7b,		/* 123 */
			0xfe,		/* 254 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IOperationQueue, ver. 0.0,
   GUID={0xc2201419,0x8d7e,0x4894,{0xb9,0xe5,0x0b,0x1d,0xa1,0x2a,0xa5,0xff}} */

#pragma code_seg(".orpc")
static const unsigned short IOperationQueue_FormatStringOffsetTable[] =
    {
    0,
    44
    };

static const MIDL_STUBLESS_PROXY_INFO IOperationQueue_ProxyInfo =
    {
    &Object_StubDesc,
    shellq__MIDL_ProcFormatString.Format,
    &IOperationQueue_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IOperationQueue_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    shellq__MIDL_ProcFormatString.Format,
    &IOperationQueue_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IOperationQueueProxyVtbl = 
{
    &IOperationQueue_ProxyInfo,
    &IID_IOperationQueue,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IOperationQueue::MoveItems */ ,
    (void *) (INT_PTR) -1 /* IOperationQueue::CopyItems */
};

const CInterfaceStubVtbl _IOperationQueueStubVtbl =
{
    &IID_IOperationQueue,
    &IOperationQueue_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    shellq__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _shellq_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IOperationQueueProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _shellq_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IOperationQueueStubVtbl,
    0
};

PCInterfaceName const _shellq_InterfaceNamesList[] = 
{
    "IOperationQueue",
    0
};


#define _shellq_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _shellq, pIID, n)

int __stdcall _shellq_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_shellq_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo shellq_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _shellq_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _shellq_StubVtblList,
    (const PCInterfaceName * ) & _shellq_InterfaceNamesList,
    0, /* no delegation */
    & _shellq_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

