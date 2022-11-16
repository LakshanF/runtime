// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#ifndef __NativeaotEventPipeSupport_h__
#define __NativeaotEventPipeSupport_h__

// This header file will contains windows header file specific definitions that NativeAOT do not use
// @Todo, this has not been formally reviewed yet

#define WINAPI      __stdcall
#define DECLSPEC_IMPORT        __declspec(dllimport)
#define APIENTRY    WINAPI
#define WINMMAPI        DECLSPEC_IMPORT

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#define far
#define near

#define FAR                 far
#define NEAR                near

#define _In_                            _SAL2_Source_(_In_, (), _Pre1_impl_(__notnull_impl_notref) _Pre_valid_impl_ _Deref_pre1_impl_(__readaccess_impl_notref))
#define _Out_                                  _SAL2_Source_(_Out_, (),     _Out_impl_)

#define MIDIPATCHSIZE   128

typedef char CHAR;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef long LONG;
typedef wchar_t WCHAR;    

typedef signed int          INT32, *PINT32;
typedef unsigned int        UINT;

typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
typedef __int64 LONG_PTR, *PLONG_PTR;
typedef unsigned __int64 UINT_PTR, *PUINT_PTR;
typedef DWORD            *LPDWORD;
typedef void             *LPVOID;
typedef void *PVOID;
typedef WORD             *LPWORD;

typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;
typedef   const WCHAR *LPCWSTR, *PCWSTR;

#ifndef __AOT_WINDOWS_DEF_NOT_NEEDED___

typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT,  *NPRECT,  *LPRECT;

struct HDC__{int unused;}; typedef struct HDC__ *HDC;

struct HWND__{int unused;}; typedef struct HWND__ *HWND;

// struct HINSTANCE__{int unused;}; typedef struct HINSTANCE__ *HINSTANCE;
// typedef HINSTANCE HMODULE;


// @TODO - 
// NativeaotEventPipeSupport.h(68): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
// NativeaotEventPipeSupport.h(68): error C2146: syntax error: missing ';' before identifier 'HMODULE'
// PalRedhawk.h(61): error C2040: 'HINSTANCE': 'void *' differs in levels of indirection from 'int'
//struct HINSTANCE__{int unused;}; typedef struct HINSTANCE__ *HINSTANCE;
//typedef HINSTANCE HMODULE;      

typedef HWND HMODULE;      

struct HTASK__{int unused;}; typedef struct HTASK__ *HTASK;
typedef HANDLE *PHANDLE;

// __declspec(dllimport)
// BOOL
// __stdcall
// FreeLibrary(
//     // See above
//       //HMODULE hLibModule
//       HANDLE hLibModule
//     );

// HMODULE
// __stdcall
// LoadLibraryW(
//       LPCWSTR lpLibFileName
//     );


// #define LoadLibrary  LoadLibraryW

#endif // __AOT_WINDOWS_DEF_NOT_NEEDED___

#endif // __NativeaotEventPipeSupport_h__