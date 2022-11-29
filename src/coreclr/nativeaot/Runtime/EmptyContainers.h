// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#ifndef __EmptyContainers_h__
#define __EmptyContainers_h__

// This header file will contains minimal containers that are needed for EventPipe library implementation
// @TODO - this will likely be replaced by the common container classes to be added to the EventPipe library

#include "forward_declarations.h"

struct SLink_EP;
typedef DPTR(struct SLink_EP) PTR_SLink_EP;

struct SLink_EP
{
    PTR_SLink_EP m_pNext;
};

template <class T, bool fHead = false, typename __PTR = T*, SLink_EP T::*LinkPtr = &T::m_Link>
class SList_EP
{
protected:
    // used as sentinel
    SLink_EP  m_link;
    PTR_SLink_EP m_pHead;
    PTR_SLink_EP m_pTail;
    // get the list node within the object
    static PTR_SLink_EP GetLink (T* pLink)
    {
        __debugbreak();
        return nullptr;
    }

    static T* GetObject (PTR_SLink_EP pLink)
    {
        __debugbreak();
        return nullptr;
    }

public:

    T*	GetHead()
    {
        __debugbreak();
        return NULL;
    }

    static T *GetNext(T *pObj)
    {
        __debugbreak();
        return NULL;
    }

    void InsertTail(T *pObj)
    {
        __debugbreak();
    }

    T* FindAndRemove(T *pObj)
    {
        __debugbreak();
        return NULL;
    }

    bool IsEmpty()
    {
        __debugbreak();
        return false;
    }

    void InsertHead(T *pObj)
    {
        __debugbreak();
    }

    T*	RemoveHead()
    {
        __debugbreak();
        return NULL;
    }

    class Iterator
    {
        friend class SList_EP;
        T* _t;

    public:
        Iterator & operator++()
        { 
            __debugbreak();
            return *this; 
        }

        Iterator operator++(int)
        { 
            __debugbreak();
            return {}; 
        }

        bool operator==(Iterator const & other) const
        {
            __debugbreak();
            return false;
        }
        T & operator*() 
        {
            __debugbreak();
            return *_t;
        }
        T * operator->() const 
        {
            __debugbreak();
            return _t;
        }
    };

    Iterator begin()
    {         
        __debugbreak();
        return Iterator(); 
    }

    Iterator end()
    { 
        __debugbreak();
        return Iterator(); 
    }

};

template <typename ElemT>
struct SListElem_EP
{
    SLink_EP m_Link;
    ElemT m_Value;

    operator ElemT const &() const
    { 
        __debugbreak();
        return m_Value; 
    }

    operator ElemT &()
    { 
        __debugbreak();
        return m_Value; 
    }

    ElemT const & operator*() const
    { 
        __debugbreak();
        return m_Value; 
    }

    ElemT & operator*()
    { 
        __debugbreak();
        return m_Value; 
    }

    SListElem_EP()
        : m_Link()
        , m_Value()
    { 
        __debugbreak();
    }

    template <typename T1>
    SListElem_EP(T1&& val)
        : m_Link()
        , m_Value(std::forward<T1>(val))
    { 
        __debugbreak();
    }

    ElemT & GetValue()
    { 
        __debugbreak();
        return m_Value; 
    }    

};

template <class T>
class CQuickArrayList_EP
{
    T _t;
public:
    T* AllocNoThrow(size_t iItems)
    {
        __debugbreak();
        return NULL;
    }

    bool PushNoThrow(const T & value)
    {
        __debugbreak();
        return false;
    }

    size_t Size() const
    {
        __debugbreak();
        return 0;
    }
    T Pop()
    {
        __debugbreak();
        return _t;
    }
    void Shrink()
    {
    }
    T& operator[] (size_t ix)
    {
        __debugbreak();
        return _t;
    }

    T* Ptr()
    {
        __debugbreak();
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
        __debugbreak();
    }

    KeyValuePair_EP(const KEY& k, const VALUE& v)
        : key(k), value(v)
    {
        __debugbreak();
    }

    KEY const & Key() const
    {
        __debugbreak();
        return key;
    }

    VALUE const & Value() const
    {
        __debugbreak();
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

    const element_t* LookupPtr(key_t key) const
    {
        __debugbreak();
        return nullptr;
    }


    class Iterator
    {
        friend class SHash_EP;
        TRAITS* _t;

    public:
        Iterator & operator++()
        { 
            __debugbreak();
            return *this; 
        }

        Iterator operator++(int)
        { 
            __debugbreak();
            return {}; 
        }

        bool operator==(Iterator const & other) const
        {
            __debugbreak();
            return false;
        }

        bool operator!=(Iterator const & other) const
        {
            __debugbreak();
            return false;
        }
        TRAITS & operator*() 
        {
            __debugbreak();
            return *_t;
        }
        TRAITS * operator->() const 
        {
            __debugbreak();
            return _t;
        }
    };

    Iterator Begin() const
    {
        __debugbreak();
        return {}; 
    }
    Iterator End() const
    {
        __debugbreak();
        return {}; 
    }
    
    bool AddNoThrow(const element_t &element)
    {
        __debugbreak();
        return false;
    }
    bool AddOrReplaceNoThrow(const element_t &element)
    {
        __debugbreak();
        return false;
    }

    count_t GetCount() const
    {
        __debugbreak();
        return 0;
    }

    void Remove(key_t key)
    {
        __debugbreak();
    }

    // Remove the specific element.
    void Remove(Iterator& i)
    {
        __debugbreak();
    }
    void RemoveAll()
    {
        __debugbreak();
    }

};

template < typename ELEMENT >
class DefaultSHashTraits_EP
{
public:
    typedef unsigned int count_t;
    typedef ELEMENT element_t;
    typedef DPTR(element_t) PTR_element_t;

    static const bool s_NoThrow = true;
};

template <typename KEY, typename VALUE>
class MapSHashTraits_EP : public DefaultSHashTraits_EP< KeyValuePair_EP<KEY,VALUE> >
{
public:
    typedef typename DefaultSHashTraits_EP< KeyValuePair_EP<KEY,VALUE> >::element_t element_t;
    typedef typename DefaultSHashTraits_EP< KeyValuePair_EP<KEY,VALUE> >::count_t count_t;

    typedef KEY key_t;
    typedef VALUE value_t;

    static key_t GetKey(element_t e)
    {
        __debugbreak();
        return e.Key();
    }
    static bool Equals(key_t k1, key_t k2)
    {
        __debugbreak();
        return k1 == k2;
    }
    static count_t Hash(key_t k)
    {
        __debugbreak();
        return (count_t)(size_t)k;
    }

    static const element_t Null() 
    { 
        __debugbreak();
        return element_t(KEY(),VALUE()); 
    }
    static const element_t Deleted() 
    { 
        __debugbreak();
        return element_t(KEY(-1), VALUE()); 
    }
    static bool IsNull(const element_t &e) { 
        __debugbreak();
        return e.Key() == KEY(); 
    }
    static bool IsDeleted(const element_t &e) 
    { 
        __debugbreak();
        return e.Key() == KEY(-1); 
    }

    key_t const & Key() const
    {
        __debugbreak();
        return *(new KEY());
    }

    value_t const & Value() const
    {
        __debugbreak();
        return *(new VALUE());
    }
};

template <typename PARENT>
class NoRemoveSHashTraits_EP : public PARENT
{
public:
    typedef typename PARENT::element_t element_t;
    typedef typename PARENT::count_t count_t;
};

#endif // __EmptyContainers_h__
