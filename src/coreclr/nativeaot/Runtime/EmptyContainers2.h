// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#ifndef __EmptyContainers2_h__
#define __EmptyContainers2_h__

// This header file will contains minimal containers that are needed for EventPipe library implementation
// @TODO - this will likely be replaced by the common container classes to be added to the EventPipe library
// Hence initially, the bare boned implementation focus is on unblocking HW/Simple Trace bring up

template <typename KEY, typename VALUE>
class KeyValuePair_EP{
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

    SHash_EP():m_table(nullptr),
    m_tableSize(0),
    m_tableCount(0),
    m_tableOccupied(0),
    m_tableMax(0)
    {        
    }

    ~SHash_EP()
    {
        delete [] m_table;
    }

    const element_t * Lookup(element_t* table, count_t tableSize, key_t key)
    {
        if (tableSize == 0)
            return NULL;

        count_t hash = TRAITS::Hash(key);
        count_t index = hash % tableSize;
        count_t increment = 0; // delay computation

        while (true)
        {
            element_t& current = table[index];

            if (TRAITS::IsNull(current))
                return NULL;

            if (!TRAITS::IsDeleted(current)
                && TRAITS::Equals(key, TRAITS::GetKey(current)))
            {
                return &current;
            }

            if (increment == 0)
                increment = (hash % (tableSize-1)) + 1;

            index += increment;
            if (index >= tableSize)
                index -= tableSize;
        }

    }

    const element_t* LookupPtr(key_t key) const
    {
        return Lookup(m_table, m_tableSize, key);        
        // __debugbreak();
        // return nullptr;
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

    // Instance members
  private:
    PTR_element_t  m_table;                // pointer to table
    count_t       m_tableSize;            // allocated size of table
    count_t       m_tableCount;           // number of elements in table
    count_t       m_tableOccupied;        // number, includes deleted slots
    count_t       m_tableMax;             // maximum occupied count before reallocating
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


#endif // __EmptyContainers2_h__
