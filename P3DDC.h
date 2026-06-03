#ifndef P3D_P3DDC_P3DDC_H
#define P3D_P3DDC_P3DDC_H




#if !defined (__cplusplus)
#error "不支持C++编译"
#endif

#if !defined (_WIN32)
#error "不是WINDOWS平台"
#endif

#if defined (_WIN32)


#pragma warning(disable:4610)
#pragma warning(disable:4510)
#pragma warning(disable:4511)
#pragma warning(disable:4512)

#pragma warning(disable:4100)
#pragma warning(disable:4706)
#pragma warning(disable:4127)
#pragma warning(disable:4266)

#pragma warning (disable: 4245)

#pragma warning (disable: 4389)

#pragma warning(disable:4201)
#pragma warning(disable:4481)
#pragma warning(disable:4480)

#pragma warning(disable:4400)
#pragma warning(disable:4611)


#define DLLPUBLIC_ATTRIBUTE

#define EXPORT_ATTRIBUTE        __declspec(dllexport)
#define IMPORT_ATTRIBUTE        __declspec(dllimport)

#define DLLLOCAL_ATTRIBUTE  
#define DLLPUBLIC_ATTRIBUTE

#define EXPORT_VTABLE_ATTRIBUTE   
#define CDECL_ATTRIBUTE         __cdecl
#define STDCALL_ATTRIBUTE       __stdcall
#define ENUM_UNDERLYING_TYPE(T)   : T

#if (_MSC_VER < 1600)
#include <limits.h>
#if defined(_M_X64)
#define INTPTR_MIN      _I64_MIN
#define INTPTR_MAX      _I64_MAX
#define UINTPTR_MAX     _UI64_MAX
#else 
#define INTPTR_MIN      _I32_MIN
#define INTPTR_MAX      _I32_MAX
#define UINTPTR_MAX     _UI32_MAX
#endif
#endif

#define HAVE_TR1
#define STD_TR1 std::tr1

#if defined(_M_X64)
typedef unsigned __int64    ULONG_PTR;
#else 
typedef __w64 unsigned long  ULONG_PTR;
#endif

#define DECLARE_KEY_METHOD
#else
#error unknown compiler
#endif

#ifdef CREATE_STATIC_LIBRARIES
#undef EXPORT_ATTRIBUTE
#undef IMPORT_ATTRIBUTE
#define EXPORT_ATTRIBUTE
#define IMPORT_ATTRIBUTE
#endif

// P3D_DEFINE_START
#if !defined (NO_P3D_STDINT_TYPEDEDFS)

#if defined (_WIN32)
#if (_MSC_VER >= 1800)
#define HAVE_STDINT
#endif

#define ALIGNMENT_ATTRIBUTE(B)

#elif defined (__unix__)
#define ALIGNMENT_ATTRIBUTE(B)  __attribute__((aligned(B)))
#define HAVE_STDINT

#else

#error unknown compiler

#endif

#ifdef HAVE_STDINT
#include <stdint.h>
#else
typedef char                int8_t;
typedef unsigned char       uint8_t;
typedef short               int16_t;
typedef unsigned short      uint16_t;
typedef int                 int32_t;
typedef unsigned int        uint32_t;
typedef long long           int64_t;
typedef unsigned long long  uint64_t;
#endif

#endif

#if !defined (NO_P3D_BASICTYPES)

typedef int8_t              Int8;
typedef uint8_t             UInt8;
typedef int16_t             Int16;
typedef uint16_t            UInt16;
typedef int32_t             Int32;
typedef uint32_t            UInt32;
typedef int64_t             Int64;
typedef uint64_t            UInt64;

typedef unsigned short      UShort;
typedef unsigned long       ULong;
typedef short               Short;
typedef unsigned int        UInt;
typedef unsigned char       UChar;
typedef unsigned char       Byte;
typedef unsigned char       byte;
typedef long                Long32;
typedef unsigned long       ULong32;

#endif


typedef uint16_t            Utf16Char;
typedef char                Utf8Char;
// P3D_DEFINE_END





#include <limits.h>

#ifndef INT32_MAX
#define INT32_MAX   INT_MAX
#endif
#ifndef UINT32_MAX
#define UINT32_MAX  UINT_MAX
#endif
#ifndef INT64_MAX
#define INT64_MAX   LLONG_MAX
#endif
#ifndef UINT64_MAX
#define UINT64_MAX  ULLONG_MAX
#endif
#ifndef INT32_MIN
#define INT32_MIN   INT_MIN
#endif
#ifndef INT64_MIN
#define INT64_MIN   LLONG_MIN
#endif

#define P3D_NAMESPACE_NAME p3d
#define BEGIN_P3D_NAMESPACE namespace P3D_NAMESPACE_NAME {
#define END_P3D_NAMESPACE   }

#define P3D_GEOMETRY_NAMESPACE_NAME p3d
#define BEGIN_P3D_GEOMETRY_NAMESPACE BEGIN_P3D_NAMESPACE
#define END_P3D_GEOMETRY_NAMESPACE   END_P3D_NAMESPACE
#define USING_NAMESPACE_P3D using namespace P3D_NAMESPACE_NAME;


#define ADD_P3D_TYPEDEFS1(_namespace_,_sourceName_,_name_,structclass) \
    namespace p3d {\
    typedef structclass _namespace_ :: _sourceName_*          _name_##P, &_name_##R;  \
    typedef structclass _namespace_ :: _sourceName_ const*    _name_##CP; \
    typedef structclass _namespace_ :: _sourceName_ const&    _name_##CR; }


#define ADD_P3D_TYPEDEFC(_namespace_,_name_) ADD_P3D_TYPEDEFS1(_namespace_,_name_,_name_,class)


#define P3D_TYPEDEFC(_name_) namespace P3D_NAMESPACE_NAME {class _name_;} ADD_P3D_TYPEDEFC(P3D_NAMESPACE_NAME,_name_)

#define P3D_REF_COUNTED_CLASS_PTR(_sname_) namespace P3D_NAMESPACE_NAME {class _sname_; typedef RefCountedPtr<_sname_> _sname_##Ptr;} 


#if !defined (_WINGDI_)
#define NOGDI
#endif                                            




#ifdef  ERROR
#undef ERROR
#endif
#ifdef  SUCCESS
#undef SUCCESS
#endif

namespace p3d
{


    enum P3DStatus
    {
        SUCCESS = 0,
        ERROR = 1,
    };

    enum class P3DCharEncoding
    {
        Locale = 0,
        Utf8 = 1
    };

    enum class P3DLangCodePage
    {
        enUnknown = -1,
        enNone = 0,
        enSimplified_Chinese = 936,
        enTraditional_Chinese = 950,
        enUnicode = 1200,
        enIsciiUnicodeUTF7 = 65000,
        enIsciiUnicodeUTF8 = 65001,
    };

    typedef int                 StatusInt;
    typedef wchar_t             WChar;
    typedef wchar_t const*      WCharCP;
    typedef wchar_t*            WCharP;
    typedef char const*         CharCP;
    typedef char*               CharP;
    typedef Utf8Char*           Utf8P;
    typedef Utf8Char const*     Utf8CP;
    typedef Utf16Char*          Utf16P;
    typedef Utf16Char const*    Utf16CP;


};


P3D_TYPEDEFC(PString)
P3D_TYPEDEFC(Utf8String)
// ____<pkpm_inner_begin>____
P3D_TYPEDEFC(P3DFileName)
// ____<pkpm_inner_end>____



#if defined (CREATE_STATIC_LIBRARIES)
#undef P3DDCDLL_EXPORT    
#define P3DDCDLL_EXPORT   
#elif !defined (P3DDCDLL_EXPORT)
#ifdef __P3DDCDLL_BUILD__
#define P3DDCDLL_EXPORT EXPORT_ATTRIBUTE
#else
#define P3DDCDLL_EXPORT IMPORT_ATTRIBUTE
#endif
#else
#undef P3DDCDLL_EXPORT    
#define P3DDCDLL_EXPORT   
#endif


#endif
