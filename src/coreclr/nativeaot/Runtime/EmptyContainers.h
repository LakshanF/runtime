// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#ifndef __EmptyContainers_h__
#define __EmptyContainers_h__

// This header file will contains minimal containers that are needed for EventPipe library implementation
// @TODO - this will likely be replaced by the common container classes to be added to the EventPipe library
// Hence initially, the bare boned implementation focus is on unblocking HW/Simple Trace bring up

struct SLink_EP
{
    SLink_EP* m_pNext;
};


// template <class T, bool fHead = false, typename __PTR = T*, SLink_EP T::*LinkPtr = &T::m_Link>
// Assumes fHead to be false
template <class T>
class SList_EP
{
protected:
    // used as sentinel
    SLink_EP  m_link;
    SLink_EP* m_pHead;
    SLink_EP* m_pTail;

    // get the list node within the object
    static SLink_EP* GetLink (T* pLink)
    {
        return &(pLink->m_Link);
    }

    static T* GetObject (SLink_EP* pLink)
    {
        if (pLink == NULL)
            return NULL;
        return reinterpret_cast<T*>(reinterpret_cast<ptrdiff_t>(pLink) - offsetof(T, m_Link));
     }

public:

    SList_EP()
    {
        m_pHead = &m_link;
        // NOTE :: fHead variable is template argument
        // the following code is a compiled in, only if the fHead flag
        // is set to false,
        m_pTail = &m_link;        
        m_link.m_pNext = NULL;
    }

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
        _ASSERTE(pObj != NULL);
        SLink_EP *pLink = GetLink(pObj);

        m_pTail->m_pNext = pLink;
        m_pTail = pLink;
    }

    T* FindAndRemove(T *pObj)
    {
        __debugbreak();
        return NULL;
    }

    bool IsEmpty()
    {
        return m_pHead->m_pNext == NULL;
    }

    void InsertHead(T *pObj)
    {
        __debugbreak();
    }

    T*	RemoveHead()
    {
        SLink_EP* pLink = m_pHead->m_pNext;
        if (pLink != NULL)
        {
            m_pHead->m_pNext = pLink->m_pNext;
        }

        if(m_pTail == pLink)
        {
            m_pTail = m_pHead;
        }

        return GetObject(pLink);
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
    }

    template <typename T1>
    SListElem_EP(T1&& val)
        : m_Link()
        , m_Value(std::forward<T1>(val))
    { 
    }

    ElemT & GetValue()
    { 
        return m_Value; 
    }    

};

// Bare boned implementation to unblock HW
template <class T>
class CQuickArrayList_EP
{
private:
    size_t m_curSize;
    T *m_array;
    size_t maxSize;
public:
    CQuickArrayList_EP()
        : m_curSize(0), maxSize(100)
    {
        m_array = new T[maxSize];
    }


    T* AllocNoThrow(size_t iItems)
    {
        return new T[iItems];
    }

    bool PushNoThrow(const T & value)
    {
        if(m_curSize >= maxSize)
            __debugbreak();
        m_array[m_curSize++] = value;
        return true;
    }

    size_t Size() const
    {
        return m_curSize;
    }
    
    T Pop()
    {
        T t = m_array[m_curSize];
        m_curSize--;
        return t;
    }

    void Shrink()
    {
    }
    
    T& operator[] (size_t ix)
    {
        return m_array[ix];
    }

    T* Ptr()
    {
        return m_array;
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
    typedef element_t* PTR_element_t;

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
