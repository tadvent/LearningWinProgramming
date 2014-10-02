

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Jun 16 22:16:56 2008
 */
/* Compiler settings for .\Lesson18.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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


#ifndef __Lesson18idl_h__
#define __Lesson18idl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DLesson18_FWD_DEFINED__
#define ___DLesson18_FWD_DEFINED__
typedef interface _DLesson18 _DLesson18;
#endif 	/* ___DLesson18_FWD_DEFINED__ */


#ifndef ___DLesson18Events_FWD_DEFINED__
#define ___DLesson18Events_FWD_DEFINED__
typedef interface _DLesson18Events _DLesson18Events;
#endif 	/* ___DLesson18Events_FWD_DEFINED__ */


#ifndef __Lesson18_FWD_DEFINED__
#define __Lesson18_FWD_DEFINED__

#ifdef __cplusplus
typedef class Lesson18 Lesson18;
#else
typedef struct Lesson18 Lesson18;
#endif /* __cplusplus */

#endif 	/* __Lesson18_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Lesson18Lib_LIBRARY_DEFINED__
#define __Lesson18Lib_LIBRARY_DEFINED__

/* library Lesson18Lib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_Lesson18Lib;

#ifndef ___DLesson18_DISPINTERFACE_DEFINED__
#define ___DLesson18_DISPINTERFACE_DEFINED__

/* dispinterface _DLesson18 */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DLesson18;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("98E6F88F-0523-4203-8423-E23733F755A7")
    _DLesson18 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DLesson18Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DLesson18 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DLesson18 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DLesson18 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DLesson18 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DLesson18 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DLesson18 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DLesson18 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DLesson18Vtbl;

    interface _DLesson18
    {
        CONST_VTBL struct _DLesson18Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DLesson18_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DLesson18_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DLesson18_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DLesson18_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DLesson18_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DLesson18_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DLesson18_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DLesson18_DISPINTERFACE_DEFINED__ */


#ifndef ___DLesson18Events_DISPINTERFACE_DEFINED__
#define ___DLesson18Events_DISPINTERFACE_DEFINED__

/* dispinterface _DLesson18Events */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DLesson18Events;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2DD40FD4-7D52-4DD6-B268-B90C42998EF9")
    _DLesson18Events : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DLesson18EventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DLesson18Events * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DLesson18Events * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DLesson18Events * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DLesson18Events * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DLesson18Events * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DLesson18Events * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DLesson18Events * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DLesson18EventsVtbl;

    interface _DLesson18Events
    {
        CONST_VTBL struct _DLesson18EventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DLesson18Events_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DLesson18Events_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DLesson18Events_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DLesson18Events_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DLesson18Events_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DLesson18Events_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DLesson18Events_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DLesson18Events_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Lesson18;

#ifdef __cplusplus

class DECLSPEC_UUID("576751F5-7D86-40BD-9872-EA1463ED0E59")
Lesson18;
#endif
#endif /* __Lesson18Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


