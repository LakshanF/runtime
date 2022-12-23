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

    SHash_EP():m_table(nullptr),m_tableSize(0){}

    const element_t * Lookup(element_t* table, count_t tableSize, key_t key)
    {
        // if (tableSize == 0)
        //     return NULL;

        // count_t hash = TRAITS::Hash(key);
        // count_t index = hash % tableSize;
        // count_t increment = 0; // delay computation

        // while (true)
        // {
        //     element_t& current = table[index];

        //     if (TRAITS::IsNull(current))
        //         return NULL;

        //     if (!TRAITS::IsDeleted(current)
        //         && TRAITS::Equals(key, TRAITS::GetKey(current)))
        //     {
        //         return &current;
        //     }

        //     if (increment == 0)
        //         increment = (hash % (tableSize-1)) + 1;

        //     index += increment;
        //     if (index >= tableSize)
        //         index -= tableSize;
        // }

        return nullptr;
    }

    const element_t* LookupPtr(key_t key) const
    {
//        return Lookup(m_table, m_tableSize, key);        
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

    // Instance members
  private:
    element_t * m_table;                // pointer to table
    count_t       m_tableSize;            // allocated size of table
    // count_t       m_tableCount;           // number of elements in table
    // count_t       m_tableOccupied;        // number, includes deleted slots
    // count_t       m_tableMax;             // maximum occupied count before reallocating


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

//////////////////////////////// AOT shash.h and shash.inl

template < typename ELEMENT, typename COUNT_T = uint32_t >
class DefaultSHashTraits_AOT
{
  public:
    typedef COUNT_T count_t;
    typedef ELEMENT element_t;
    typedef DPTR(element_t) PTR_element_t;   // by default SHash is DAC-aware. For RS
                                             // only SHash use NonDacAwareSHashTraits
                                             // (which typedefs element_t* PTR_element_t)
    static const count_t s_growth_factor_numerator = 3;
    static const count_t s_growth_factor_denominator = 2;

    static const count_t s_density_factor_numerator = 3;
    static const count_t s_density_factor_denominator = 4;

    static const count_t s_minimum_allocation = 7;

    static const bool s_supports_remove = true;

    static const ELEMENT Null() { return (const ELEMENT) 0; }
    static const ELEMENT Deleted() { return (const ELEMENT) -1; }
    static bool IsNull(const ELEMENT &e) { return e == (const ELEMENT) 0; }
    static bool IsDeleted(const ELEMENT &e) { return e == (const ELEMENT) -1; }

    static void OnFailure(FailureType /*ft*/) { }
    
    // No defaults - must specify:
    //
    // typedef key_t;
    // static key_t GetKey(const element_t &i);
    // static bool Equals(key_t k1, key_t k2);
    // static count_t Hash(key_t k);
};

template <typename KEY, typename VALUE>
class MapSHashTraits_AOT : public DefaultSHashTraits_AOT< KeyValuePair_EP<KEY,VALUE> >
{
public:
    // explicitly declare local typedefs for these traits types, otherwise
    // the compiler may get confused
    typedef typename DefaultSHashTraits_AOT< KeyValuePair_EP<KEY,VALUE> >::element_t element_t;
    typedef typename DefaultSHashTraits_AOT< KeyValuePair_EP<KEY,VALUE> >::count_t count_t;

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

    static const element_t Null() { return element_t((KEY)0,(VALUE)0); }
    static bool IsNull(const element_t &e) { return e.Key() == (KEY)0; }
};

template <typename PARENT>
class NoRemoveSHashTraits_AOT : public PARENT
{
public:
    // explicitly declare local typedefs for these traits types, otherwise
    // the compiler may get confused
    typedef typename PARENT::element_t element_t;
    typedef typename PARENT::count_t count_t;

    static const bool s_supports_remove = false;
    static const element_t Deleted() { UNREACHABLE(); }
    static bool IsDeleted(const element_t &e) { UNREFERENCED_PARAMETER(e); return false; }
};

// Hash table class definition

template <typename TRAITS>
class SHash_AOT : public TRAITS
{
  private:
    class Index;
    friend class Index;

    class KeyIndex;
    friend class KeyIndex;
    class Iterator;
    class KeyIterator;

  public:
    // explicitly declare local typedefs for these traits types, otherwise
    // the compiler may get confused
    typedef typename TRAITS::element_t element_t;
    typedef typename TRAITS::PTR_element_t PTR_element_t;
    typedef typename TRAITS::key_t key_t;
    typedef typename TRAITS::count_t count_t;

    // Constructor/destructor.  SHash tables always start out empty, with no
    // allocation overhead.  Call Reallocate to prime with an initial size if
    // desired.

    SHash_AOT();
    ~SHash_AOT();

    // Lookup an element in the table by key.  Returns NULL if no element in the table
    // has the given key.  Note that multiple entries for the same key may be stored -
    // this will return the first element added.  Use KeyIterator to find all elements
    // with a given key.

    element_t Lookup(key_t key) const;

    // Pointer-based flavor of Lookup (allows efficient access to tables of structures)

    const element_t* LookupPtr(key_t key) const;

    // Add an element to the hash table.  This will never replace an element; multiple
    // elements may be stored with the same key.
    //
    // Returns 'true' on success, 'false' on failure.

    bool Add(const element_t &element);

    // Add a new element to the hash table, if no element with the same key is already
    // there. Otherwise, it will replace the existing element. This has the effect of
    // updating an element rather than adding a duplicate.
    //
    // Returns 'true' on success, 'false' on failure.

    bool AddOrReplace(const element_t & element);

    // Remove the first element matching the key from the hash table.

    void Remove(key_t key);

    // Remove the specific element.

    void Remove(Iterator& i);
    void Remove(KeyIterator& i);

    // Pointer-based flavor of Remove (allows efficient access to tables of structures)

    void RemovePtr(element_t * element);

    // Remove all elements in the hashtable

    void RemoveAll();

    // Begin and End pointers for iteration over entire table.

    Iterator Begin() const;
    Iterator End() const;

    // Begin and End pointers for iteration over all elements with a given key.

    KeyIterator Begin(key_t key) const;
    KeyIterator End(key_t key) const;

    // Return the number of elements currently stored in the table

    count_t GetCount() const;

    // Return the number of elements that the table is capable storing currently

    count_t GetCapacity() const;

    // Reallocates a hash table to a specific size.  The size must be big enough
    // to hold all elements in the table appropriately.
    //
    // Note that the actual table size must always be a prime number; the number
    // passed in will be upward adjusted if necessary.
    //
    // Returns 'true' on success, 'false' on failure.

    bool Reallocate(count_t newTableSize);

    // See if it is OK to grow the hash table by one element.  If not, reallocate
    // the hash table.
    //
    // Returns 'true' on success, 'false' on failure.

    bool CheckGrowth();

    // See if it is OK to grow the hash table by N elementsone element.  If not, reallocate
    // the hash table.

    bool CheckGrowth(count_t newElements);

private:

    // Resizes a hash table for growth.  The new size is computed based
    // on the current population, growth factor, and maximum density factor.
    //
    // Returns 'true' on success, 'false' on failure.

    bool Grow();

    // Utility function to add a new element to the hash table.  Note that
    // it is perfectly find for the element to be a duplicate - if so it
    // is added an additional time. Returns true if a new empty spot was used;
    // false if an existing deleted slot.

    static bool Add(element_t *table, count_t tableSize, const element_t &element);

    // Utility function to add a new element to the hash table, if no element with the same key
    // is already there. Otherwise, it will replace the existing element. This has the effect of
    // updating an element rather than adding a duplicate.

    void AddOrReplace(element_t *table, count_t tableSize, const element_t &element);

    // Utility function to find the first element with the given key in
    // the hash table.

    static const element_t* Lookup(PTR_element_t table, count_t tableSize, key_t key);

    // Utility function to remove the first element with the given key
    // in the hash table.

    void Remove(element_t *table, count_t tableSize, key_t key);

    // Utility function to remove the specific element.

    void RemoveElement(element_t *table, count_t tableSize, element_t *element);

    //
    // Enumerator, provides a template to produce an iterator on an existing class
    // with a single iteration variable.
    //

    template <typename SUBTYPE>
    class Enumerator
    {
     private:
        const SUBTYPE *This() const
        {
            return (const SUBTYPE *) this;
        }

        SUBTYPE *This()
        {
            return (SUBTYPE *)this;
        }

      public:

        Enumerator()
        {
        }

        const element_t &operator*() const
        {
            return This()->Get();
        }
        const element_t *operator->() const
        {
            return &(This()->Get());
        }
        SUBTYPE &operator++()
        {
            This()->Next();
            return *This();
        }
        SUBTYPE operator++(int)
        {
            SUBTYPE i = *This();
            This()->Next();
            return i;
        }
        bool operator==(const SUBTYPE &i) const
        {
            return This()->Equal(i);
        }
        bool operator!=(const SUBTYPE &i) const
        {
            return !This()->Equal(i);
        }
    };

    //
    // Index for whole table iterator.  This is also the base for the keyed iterator.
    //

    class Index
    {
        friend class SHash_AOT;
        friend class Iterator;
        friend class Enumerator<Iterator>;

        // The methods implementation has to be here for portability
        // Some compilers won't compile the separate implementation in shash.inl
      protected:

        PTR_element_t m_table;
        count_t m_tableSize;
        count_t m_index;

        Index(const SHash_AOT *hash, bool begin)
        : m_table(hash->m_table),
            m_tableSize(hash->m_tableSize),
            m_index(begin ? 0 : m_tableSize)
        {
        }

        const element_t &Get() const
        {
            return m_table[m_index];
        }

        void First()
        {
            if (m_index < m_tableSize)
                if (TRAITS::IsNull(m_table[m_index]) || TRAITS::IsDeleted(m_table[m_index]))
                    Next();
        }

        void Next()
        {
            if (m_index >= m_tableSize)
                return;

            for (;;)
            {
                m_index++;
                if (m_index >= m_tableSize)
                    break;
                if (!TRAITS::IsNull(m_table[m_index]) && !TRAITS::IsDeleted(m_table[m_index]))
                    break;
            }
        }

        bool Equal(const Index &i) const
        {
            return i.m_index == m_index;
        }
    };

    class Iterator : public Index, public Enumerator<Iterator>
    {
        friend class SHash_AOT;

      public:
        Iterator(const SHash_AOT *hash, bool begin)
          : Index(hash, begin)
        {
        }
    };

    //
    // Index for iterating elements with a given key.
    // Note that the m_index field is artificially bumped to m_tableSize when the end
    // of iteration is reached. This allows a canonical End iterator to be used.
    //

    class KeyIndex : public Index
    {
        friend class SHash_AOT;
        friend class KeyIterator;
        friend class Enumerator<KeyIterator>;

        // The methods implementation has to be here for portability
        // Some compilers won't compile the separate implementation in shash.inl
      protected:
        key_t       m_key;
        count_t     m_increment;

        KeyIndex(const SHash_AOT *hash, bool begin)
        : Index(hash, begin),
            m_increment(0)
        {
        }

        void SetKey(key_t key)
        {
            if (m_tableSize > 0)
            {
                m_key = key;
                count_t hash = Hash(key);

                TRAITS::m_index = hash % m_tableSize;
                m_increment = (hash % (m_tableSize-1)) + 1;

                // Find first valid element
                if (IsNull(m_table[TRAITS::m_index]))
                    TRAITS::m_index = m_tableSize;
                else if (IsDeleted(m_table[TRAITS::m_index])
                        || !Equals(m_key, GetKey(m_table[TRAITS::m_index])))
                    Next();
            }
        }

        void Next()
        {
            while (true)
            {
                TRAITS::m_index += m_increment;
                if (TRAITS::m_index >= m_tableSize)
                    TRAITS::m_index -= m_tableSize;

                if (IsNull(m_table[TRAITS::m_index]))
                {
                    TRAITS::m_index = m_tableSize;
                    break;
                }

                if (!IsDeleted(m_table[TRAITS::m_index])
                        && Equals(m_key, GetKey(m_table[TRAITS::m_index])))
                {
                    break;
                }
            }
        }
    };

    class KeyIterator : public KeyIndex, public Enumerator<KeyIterator>
    {
        friend class SHash_AOT;

      public:

        operator Iterator &()
        {
            return *(Iterator*)this;
        }

        operator const Iterator &()
        {
            return *(const Iterator*)this;
        }

        KeyIterator(const SHash_AOT *hash, bool begin)
          : KeyIndex(hash, begin)
        {
        }
    };

    // Test for prime number.
    static bool IsPrime(count_t number);

    // Find the next prime number >= the given value.

    static count_t NextPrime(count_t number);

    // Instance members

    PTR_element_t m_table;                // pointer to table
    count_t       m_tableSize;            // allocated size of table
    count_t       m_tableCount;           // number of elements in table
    count_t       m_tableOccupied;        // number, includes deleted slots
    count_t       m_tableMax;             // maximum occupied count before reallocating
};

// disable the "Conditional expression is constant" warning
//#pragma warning(disable:4127)


template <typename TRAITS>
SHash_AOT<TRAITS>::SHash_AOT()
  : m_table(nullptr),
    m_tableSize(0),
    m_tableCount(0),
    m_tableOccupied(0),
    m_tableMax(0)
{
    // C_ASSERT(TRAITS::s_growth_factor_numerator > TRAITS::s_growth_factor_denominator);
    // C_ASSERT(TRAITS::s_density_factor_numerator < TRAITS::s_density_factor_denominator);
}

template <typename TRAITS>
SHash_AOT<TRAITS>::~SHash_AOT()
{
    delete [] m_table;
}

template <typename TRAITS>
typename SHash_AOT<TRAITS>::count_t SHash_AOT<TRAITS>::GetCount() const
{
    return m_tableCount;
}

template <typename TRAITS>
typename SHash_AOT<TRAITS>::count_t SHash_AOT<TRAITS>::GetCapacity() const
{
    return m_tableMax;
}

template <typename TRAITS>
typename SHash_AOT< TRAITS>::element_t SHash_AOT<TRAITS>::Lookup(key_t key) const
{
    const element_t *pRet = Lookup(m_table, m_tableSize, key);
    return ((pRet != NULL) ? (*pRet) : TRAITS::Null());
}

template <typename TRAITS>
const typename SHash_AOT< TRAITS>::element_t* SHash_AOT<TRAITS>::LookupPtr(key_t key) const
{
    return Lookup(m_table, m_tableSize, key);
}

template <typename TRAITS>
bool SHash_AOT<TRAITS>::Add(const element_t &element)
{
    if (!CheckGrowth())
        return false;

    if (Add(m_table, m_tableSize, element))
        m_tableOccupied++;
    m_tableCount++;

    return true;
}

template <typename TRAITS>
bool SHash_AOT<TRAITS>::AddOrReplace(const element_t &element)
{
    if (!CheckGrowth())
        return false;

    AddOrReplace(m_table, m_tableSize, element);
    return true;
}

template <typename TRAITS>
void SHash_AOT<TRAITS>::Remove(key_t key)
{
    Remove(m_table, m_tableSize, key);
}

template <typename TRAITS>
void SHash_AOT<TRAITS>::Remove(Iterator& i)
{
    RemoveElement(m_table, m_tableSize, (element_t*)&(*i));
}

template <typename TRAITS>
void SHash_AOT<TRAITS>::Remove(KeyIterator& i)
{
    RemoveElement(m_table, m_tableSize, (element_t*)&(*i));
}

template <typename TRAITS>
void SHash_AOT<TRAITS>::RemovePtr(element_t * p)
{
    RemoveElement(m_table, m_tableSize, p);
}

template <typename TRAITS>
void SHash_AOT<TRAITS>::RemoveAll()
{
    delete [] m_table;

    m_table = NULL;
    m_tableSize = 0;
    m_tableCount = 0;
    m_tableOccupied = 0;
    m_tableMax = 0;
}

template <typename TRAITS>
typename SHash_AOT<TRAITS>::Iterator SHash_AOT<TRAITS>::Begin() const
{
    Iterator i(this, true);
    i.First();
    return i;
}

template <typename TRAITS>
typename SHash_AOT<TRAITS>::Iterator SHash_AOT<TRAITS>::End() const
{
    return Iterator(this, false);
}

template <typename TRAITS>
typename SHash_AOT<TRAITS>::KeyIterator SHash_AOT<TRAITS>::Begin(key_t key) const
{
    KeyIterator k(this, true);
    k.SetKey(key);
    return k;
}

template <typename TRAITS>
typename SHash_AOT<TRAITS>::KeyIterator SHash_AOT<TRAITS>::End(key_t key) const
{
    return KeyIterator(this, false);
}

template <typename TRAITS>
bool SHash_AOT<TRAITS>::CheckGrowth()
{
    if (m_tableOccupied == m_tableMax)
    {
        return Grow();
    }

    return true;
}

template <typename TRAITS>
bool SHash_AOT<TRAITS>::Grow()
{
    count_t newSize = (count_t) (m_tableCount
                                 * TRAITS::s_growth_factor_numerator / TRAITS::s_growth_factor_denominator
                                 * TRAITS::s_density_factor_denominator / TRAITS::s_density_factor_numerator);
    if (newSize < TRAITS::s_minimum_allocation)
        newSize = TRAITS::s_minimum_allocation;

    // handle potential overflow
    if (newSize < m_tableCount)
    {
        TRAITS::OnFailure(ftOverflow);
        return false;
    }

    return Reallocate(newSize);
}

template <typename TRAITS>
bool SHash_AOT<TRAITS>::CheckGrowth(count_t newElements)
{
    count_t newCount = (m_tableCount + newElements);

    // handle potential overflow
    if (newCount < newElements)
    {
        TRAITS::OnFailure(ftOverflow);
        return false;
    }

    // enough space in the table?
    if (newCount < m_tableMax)
        return true;

    count_t newSize = (count_t) (newCount * TRAITS::s_density_factor_denominator / TRAITS::s_density_factor_numerator) + 1;

    // handle potential overflow
    if (newSize < newCount)
    {
        TRAITS::OnFailure(ftOverflow);
        return false;
    }

    // accelerate the growth to avoid unnecessary rehashing
    count_t newSize2 = (m_tableCount * TRAITS::s_growth_factor_numerator / TRAITS::s_growth_factor_denominator
                                     * TRAITS::s_density_factor_denominator / TRAITS::s_density_factor_numerator);

    if (newSize < newSize2)
        newSize = newSize2;

    if (newSize < TRAITS::s_minimum_allocation)
        newSize = TRAITS::s_minimum_allocation;

    return Reallocate(newSize);
}

template <typename TRAITS>
bool SHash_AOT<TRAITS>::Reallocate(count_t newTableSize)
{
    ASSERT(newTableSize >=
                 (count_t) (GetCount() * TRAITS::s_density_factor_denominator / TRAITS::s_density_factor_numerator));

    // Allocation size must be a prime number.  This is necessary so that hashes uniformly
    // distribute to all indices, and so that chaining will visit all indices in the hash table.
    newTableSize = NextPrime(newTableSize);
    if (newTableSize == 0)
    {
        TRAITS::OnFailure(ftOverflow);
        return false;
    }

    element_t *newTable = new (nothrow) element_t [newTableSize];
    if (newTable == NULL)
    {
        TRAITS::OnFailure(ftAllocation);
        return false;
    }

    element_t *p = newTable, *pEnd = newTable + newTableSize;
    while (p < pEnd)
    {
        *p = TRAITS::Null();
        p++;
    }

    // Move all entries over to new table.

    for (Iterator i = Begin(), end = End(); i != end; i++)
    {
        const element_t & cur = (*i);
        if (!TRAITS::IsNull(cur) && !TRAITS::IsDeleted(cur))
            Add(newTable, newTableSize, cur);
    }

    // @todo:
    // We might want to try to delay this cleanup to allow asynchronous readers

    delete [] m_table;

    m_table = PTR_element_t(newTable);
    m_tableSize = newTableSize;
    m_tableMax = (count_t) (newTableSize * TRAITS::s_density_factor_numerator / TRAITS::s_density_factor_denominator);
    m_tableOccupied = m_tableCount;

    return true;
}

template <typename TRAITS>
const typename SHash_AOT<TRAITS>::element_t * SHash_AOT<TRAITS>::Lookup(PTR_element_t table, count_t tableSize, key_t key)
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

template <typename TRAITS>
bool SHash_AOT<TRAITS>::Add(element_t *table, count_t tableSize, const element_t &element)
{
    key_t key = TRAITS::GetKey(element);

    count_t hash = TRAITS::Hash(key);
    count_t index = hash % tableSize;
    count_t increment = 0; // delay computation

    while (true)
    {
        element_t& current = table[index];

        if (TRAITS::IsNull(current))
        {
            table[index] = element;
            return true;
        }

        if (TRAITS::IsDeleted(current))
        {
            table[index] = element;
            return false;
        }

        if (increment == 0)
            increment = (hash % (tableSize-1)) + 1;

        index += increment;
        if (index >= tableSize)
            index -= tableSize;
    }
}

template <typename TRAITS>
void SHash_AOT<TRAITS>::AddOrReplace(element_t *table, count_t tableSize, const element_t &element)
{
    ASSERT(!TRAITS::s_supports_remove);

    key_t key = TRAITS::GetKey(element);

    count_t hash = TRAITS::Hash(key);
    count_t index = hash % tableSize;
    count_t increment = 0; // delay computation

    while (true)
    {
        element_t& current = table[index];
        ASSERT(!TRAITS::IsDeleted(current));

        if (TRAITS::IsNull(current))
        {
            table[index] = element;
            m_tableCount++;
            m_tableOccupied++;
            return;
        }
        else if (TRAITS::Equals(key, TRAITS::GetKey(current)))
        {
            table[index] = element;
            return;
        }

        if (increment == 0)
            increment = (hash % (tableSize-1)) + 1;

        index += increment;
        if (index >= tableSize)
            index -= tableSize;
    }
}

#ifdef _MSC_VER
#pragma warning (disable: 4702) // Workaround bogus unreachable code warning
#endif
template <typename TRAITS>
void SHash_AOT<TRAITS>::Remove(element_t *table, count_t tableSize, key_t key)
{
    ASSERT(TRAITS::s_supports_remove);
    ASSERT(Lookup(table, tableSize, key) != NULL);

    count_t hash = TRAITS::Hash(key);
    count_t index = hash % tableSize;
    count_t increment = 0; // delay computation

    while (true)
    {
        element_t& current = table[index];

        if (TRAITS::IsNull(current))
            return;

        if (!TRAITS::IsDeleted(current)
            && TRAITS::Equals(key, TRAITS::GetKey(current)))
        {
            table[index] = TRAITS::Deleted();
      	    m_tableCount--;
            return;
        }

        if (increment == 0)
            increment = (hash % (tableSize-1)) + 1;

        index += increment;
        if (index >= tableSize)
            index -= tableSize;
    }
}
#ifdef _MSC_VER
#pragma warning (default: 4702)
#endif

template <typename TRAITS>
void SHash_AOT<TRAITS>::RemoveElement(element_t *table, count_t tableSize, element_t *element)
{
    ASSERT(TRAITS::s_supports_remove);
    ASSERT(table <= element && element < table + tableSize);
    ASSERT(!TRAITS::IsNull(*element) && !TRAITS::IsDeleted(*element));

    *element = TRAITS::Deleted();
    m_tableCount--;
}

template <typename TRAITS>
bool SHash_AOT<TRAITS>::IsPrime(count_t number)
{
    // This is a very low-tech check for primality, which doesn't scale very well.
    // There are more efficient tests if this proves to be burdensome for larger
    // tables.

    if ((number&1) == 0)
        return false;

    count_t factor = 3;
    while (factor * factor <= number)
    {
        if ((number % factor) == 0)
            return false;
        factor += 2;
    }

    return true;
}

namespace
{
    const uint32_t g_shash_primes[] = {
        11,17,23,29,37,47,59,71,89,107,131,163,197,239,293,353,431,521,631,761,919,
        1103,1327,1597,1931,2333,2801,3371,4049,4861,5839,7013,8419,10103,12143,14591,
        17519,21023,25229,30293,36353,43627,52361,62851,75431,90523, 108631, 130363,
        156437, 187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403,
        968897, 1162687, 1395263, 1674319, 2009191, 2411033, 2893249, 3471899, 4166287,
        4999559, 5999471, 7199369 };
}


// Returns a prime larger than 'number' or 0, in case of overflow
template <typename TRAITS>
typename SHash_AOT<TRAITS>::count_t SHash_AOT<TRAITS>::NextPrime(typename SHash_AOT<TRAITS>::count_t number)
{
    for (int i = 0; i < (int) (sizeof(g_shash_primes) / sizeof(g_shash_primes[0])); i++)
    {
        if (g_shash_primes[i] >= number)
            return (typename SHash_AOT<TRAITS>::count_t)(g_shash_primes[i]);
    }

    if ((number&1) == 0)
        number++;

    while (number != 1)
    {
        if (IsPrime(number))
            return number;
        number += 2;
    }

    return 0;
}

// restore "Conditional expression is constant" warning to default value
//#pragma warning(default:4127)

#endif // __EmptyContainers2_h__
