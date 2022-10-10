// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#ifndef __slist_h__
#define __slist_h__

#include "forward_declarations.h"

MSVC_SAVE_WARNING_STATE()
MSVC_DISABLE_WARNING(4127)  // conditional expression is constant -- it's intentionally constant

struct SLink;
typedef DPTR(struct SLink) PTR_SLink;

struct SLink
{
};

template <class T, bool fHead = false, typename __PTR = T*, SLink T::*LinkPtr = &T::m_Link>
class SList
{
public:
    class Iterator
    {
        friend class SList;
    };
};

template <typename ElemT>
struct SListElem
{
    SLink m_Link;
    ElemT m_Value;

    ElemT & GetValue()
    { return m_Value; }

};

template <class T>
class CQuickArrayList //: protected CQuickArray<T>
{
};

template <typename KEY, typename VALUE>
class KeyValuePair {
};

template <typename TRAITS>
class SHash : public TRAITS
{
  public:
    class Iterator;
};

// template <typename PARENT>
// class /**EMPTY_BASES_DECL**/ NoRemoveSHashTraits : public PARENT
// {
// };

template < typename ELEMENT, typename COUNT_T = uint32_t >
class DefaultSHashTraits
{
};

template <typename KEY, typename VALUE>
class /*EMPTY_BASES_DECL*/ MapSHashTraits : public DefaultSHashTraits< KeyValuePair<KEY,VALUE> >
{
};

MSVC_RESTORE_WARNING_STATE()

#endif // __slist_h__
