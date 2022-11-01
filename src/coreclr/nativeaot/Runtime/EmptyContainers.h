// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#ifndef __slist_h__
#define __slist_h__

//#include <windows.h>
#include "forward_declarations.h"

// MSVC_SAVE_WARNING_STATE()
// MSVC_DISABLE_WARNING(4127)  // conditional expression is constant -- it's intentionally constant

// struct SLink_EP;
// typedef DPTR(struct SLink_EP) PTR_SLink;

struct SLink_EP
{
    SLink_EP* m_pNext;
};

template <class T, bool fHead = false, typename __PTR = T*, SLink_EP T::*LinkPtr = &T::m_Link>
class SList_EP
{
protected:
    // used as sentinel
    SLink_EP  m_link; // slink.m_pNext == Null
    SLink_EP* m_pHead;
    SLink_EP* m_pTail;
    // get the list node within the object
    static SLink_EP* GetLink (T* pLink)
    {
        return nullptr;
    }

    static T* GetObject (SLink_EP* pLink)
    {
        return nullptr;
    }

public:

    T*	GetHead()
    {
        return NULL;
    }

    static T *GetNext(T *pObj)
    {
        return NULL;
    }

    void InsertTail(T *pObj){}

    T* FindAndRemove(T *pObj)
    {
        return NULL;
    }

    bool IsEmpty()
    {
        return false;
    }

    void InsertHead(T *pObj)
    {
    }

    T*	RemoveHead()
    {
        return NULL;
    }

    class Iterator
    {
        friend class SList_EP;
        T* _t;

    public:
        Iterator & operator++()
        { return *this; }

        Iterator operator++(int)
        { return {}; }

        bool operator==(Iterator const & other) const
        {
            return false;
        }
        T & operator*() {return *_t;}
        T * operator->() const {return _t;}
    };

    Iterator begin()
    { return Iterator(); }

    Iterator end()
    { return Iterator(); }

};

template <typename ElemT>
struct SListElem_EP
{
    SLink_EP m_Link;
    ElemT m_Value;

    operator ElemT const &() const
    { return m_Value; }

    operator ElemT &()
    { return m_Value; }

    ElemT const & operator*() const
    { return m_Value; }

    ElemT & operator*()
    { return m_Value; }

    SListElem_EP()
        : m_Link()
        , m_Value()
    { }

    template <typename T1>
    SListElem_EP(T1&& val)
        : m_Link()
        , m_Value(std::forward<T1>(val))
    { }

    ElemT & GetValue()
    { return m_Value; }    

};

template <class T>
class CQuickArrayList_EP //: protected CQuickArray<T>
{
    T _t;
public:
    T* AllocNoThrow(size_t iItems)
    {
        return NULL;
    }

    bool PushNoThrow(const T & value)
    {
        return false;
    }

    size_t Size() const
    {
        return 0;
    }
    T Pop()
    {
        return _t;
    }
    void Shrink()
    {
    }
    T& operator[] (size_t ix)
    {
        return _t;
    }

    T* Ptr()
    {
        return NULL;
    }
};

template <typename KEY, typename VALUE>
class KeyValuePair_EP {
    KEY     key;
    VALUE   value;
public:
    KeyValuePair_EP()
    {
    }

    KeyValuePair_EP(const KEY& k, const VALUE& v)
        : key(k), value(v)
    {
    }

    KEY const & Key() const
    {
        return key;
    }

    VALUE const & Value() const
    {
        return value;
    }

};

template <typename TRAITS>
class SHash_EP : public TRAITS
{
  public:
    typedef typename TRAITS::element_t element_t;
    typedef typename TRAITS::PTR_element_t PTR_element_t;
    typedef typename TRAITS::key_t key_t;
    typedef typename TRAITS::count_t count_t;

    const element_t* LookupPtr(key_t key) const{return nullptr;}


    class Iterator
    {
        friend class SHash_EP;
        TRAITS* _t;

    public:
        Iterator & operator++()
        { return *this; }

        Iterator operator++(int)
        { return {}; }

        bool operator==(Iterator const & other) const
        {
            return false;
        }

        bool operator!=(Iterator const & other) const
        {
            return false;
        }
        TRAITS & operator*() {return *_t;}
        TRAITS * operator->() const {return _t;}
        // TRAITS const & Value() const
        // {
        //     return _t;
        // }
    };

    Iterator Begin() const{return {}; }
    Iterator End() const{return {}; }
    
    bool AddNoThrow(const element_t &element){return false;}
    bool AddOrReplaceNoThrow(const element_t &element){return false;}

    count_t GetCount() const{return 0;}

    void Remove(key_t key){}

    // Remove the specific element.

    void Remove(Iterator& i){}
    //void Remove(KeyIterator& i){}
    void RemoveAll(){}

};

//template < typename ELEMENT, typename COUNT_T = uint32_t >
template < typename ELEMENT >
class DefaultSHashTraits_EP
{
public:
    typedef unsigned int count_t;
    typedef ELEMENT element_t;
//    typedef DPTR(element_t) PTR_element_t;   // by default SHash_EP is DAC-aware. For RS
    typedef element_t* PTR_element_t;   // by default SHash_EP is DAC-aware. For RS
};

template <typename KEY, typename VALUE>
class MapSHashTraits_EP : public DefaultSHashTraits_EP< KeyValuePair_EP<KEY,VALUE> >
{
public:
    typedef typename DefaultSHashTraits_EP< KeyValuePair_EP<KEY,VALUE> >::element_t element_t;
    typedef typename DefaultSHashTraits_EP< KeyValuePair_EP<KEY,VALUE> >::count_t count_t;

    typedef KEY key_t;

    static key_t GetKey(element_t e)
    {
        return e.Key();
    }
    static bool Equals(key_t k1, key_t k2)
    {
        return k1 == k2;
    }
    static count_t Hash(key_t k)
    {
        return (count_t)(size_t)k;
    }

    static const element_t Null() { return element_t(KEY(),VALUE()); }
    static const element_t Deleted() { return element_t(KEY(-1), VALUE()); }
    static bool IsNull(const element_t &e) { return e.Key() == KEY(); }
    static bool IsDeleted(const element_t &e) { return e.Key() == KEY(-1); }
};

template <typename PARENT>
class NoRemoveSHashTraits_EP : public PARENT
{
public:
    // explicitly declare local typedefs for these traits types, otherwise
    // the compiler may get confused
    typedef typename PARENT::element_t element_t;
    typedef typename PARENT::count_t count_t;

    // static const bool s_supports_remove = false;
    // static element_t Deleted() { UNREACHABLE(); }
    // static bool IsDeleted(const element_t &e) { LIMITED_METHOD_DAC_CONTRACT; return false; }
};


// MSVC_RESTORE_WARNING_STATE()

#endif // __slist_h__
