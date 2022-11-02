
#define WINAPI      __stdcall
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

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
// typedef float               FLOAT;
// typedef FLOAT               *PFLOAT;
// typedef BOOL            *PBOOL;
// typedef BOOL             *LPBOOL;
// typedef BYTE            *PBYTE;
// typedef BYTE             *LPBYTE;
// typedef int             *PINT;
// typedef int              *LPINT;
// typedef WORD            *PWORD;
// typedef WORD             *LPWORD;
// typedef long             *LPLONG;
// typedef DWORD           *PDWORD;
// typedef DWORD            *LPDWORD;
// typedef void             *LPVOID;
// typedef const void       *LPCVOID;

// typedef int                 INT;
typedef unsigned int        UINT;
// typedef unsigned int        *PUINT;

typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;

// #define CALLBACK    __stdcall
//#define pascal __stdcall
// #define WINAPIV     __cdecl
// #define APIENTRY    WINAPI
// #define APIPRIVATE  __stdcall
// #define PASCAL      __stdcall


// typedef struct mmtime_tag {
//   UINT wType;
//   union {
//     DWORD ms;
//     DWORD sample;
//     DWORD cb;
//     DWORD ticks;
//     struct {
//       BYTE hour;
//       BYTE min;
//       BYTE sec;
//       BYTE frame;
//       BYTE fps;
//       BYTE dummy;
//       BYTE pad[2];
//     }smpte;
//     struct {
//       DWORD songptrpos;
//     }midi;
//   }u;
// } MMTIME, *PMMTIME, *LPMMTIME;

// typedef struct _FILETIME {
//     DWORD dwLowDateTime;
//     DWORD dwHighDateTime;
// } FILETIME, *PFILETIME, *LPFILETIME;
// #define _FILETIME_

// EXTERN_C long __cdecl _InterlockedIncrement(long volatile *);
// #pragma intrinsic(_InterlockedIncrement)
// FORCEINLINE int32_t PalInterlockedIncrement(_Inout_ int32_t volatile *pDst)
// {
//     return _InterlockedIncrement((long volatile *)pDst);
// }

// EXTERN_C long __cdecl _InterlockedDecrement(long volatile *);
// #pragma intrinsic(_InterlockedDecrement)
// FORCEINLINE int32_t PalInterlockedDecrement(_Inout_ int32_t volatile *pDst)
// {
//     return _InterlockedDecrement((long volatile *)pDst);
// }
