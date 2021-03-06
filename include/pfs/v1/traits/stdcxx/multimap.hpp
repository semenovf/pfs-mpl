#ifndef __PFS_TRAITS_STDCXX_MULTIMAP_HPP__
#define __PFS_TRAITS_STDCXX_MULTIMAP_HPP__

#include <map>
#include <pfs/traits/value_ref.hpp>

namespace pfs {
namespace stdcxx {

template <typename KvType>
struct multimap_wrapper
{
    typedef std::multimap<typename KvType::key_type, typename KvType::mapped_type> type;
};

template <typename KvType, typename ValueOrReference>
class multimap_basic
{
    typedef ValueOrReference internal_type;

public:
    typedef multimap_basic<KvType, traits::container_value<KvType, multimap_wrapper> > container_value_type;
    typedef multimap_basic<KvType, traits::container_reference<KvType, multimap_wrapper> >   container_reference_type;
    
    typedef typename internal_type::native_type            native_type;
    typedef typename internal_type::native_reference       native_reference;
    typedef typename internal_type::const_native_reference const_native_reference;
    
    typedef typename native_type::value_type       value_type;
    //typedef typename native_type::const_pointer    const_pointer;
    //typedef typename native_type::reference        reference;
    //typedef typename native_type::const_reference  const_reference;
    typedef typename native_type::iterator         iterator;
    typedef typename native_type::const_iterator   const_iterator;
    typedef typename native_type::reverse_iterator reverse_iterator;
    typedef typename native_type::const_reverse_iterator const_reverse_iterator;
    typedef typename native_type::difference_type  difference_type;
    typedef typename native_type::size_type        size_type;
    
    typedef typename native_type::key_type         key_type;
    typedef typename native_type::mapped_type      mapped_type;
    
    typedef typename native_type::key_compare      key_compare;
    typedef typename native_type::value_compare    value_compare;

protected:
    internal_type _p;
    
public:
    multimap_basic ()
    {}

    multimap_basic (native_reference rhs)
        : _p(rhs)
    {}

    multimap_basic (const_native_reference rhs)
        : _p(rhs)
    {}
    
//    multimap (const_pointer s)
//        : _p(s)
//    {}
//
//    template <typename InputIt>
//    basic_string (InputIt first, InputIt last)
//        : _p(first, last)
//    {}
    
    multimap_basic & operator = (native_reference rhs)
    {
        *_p = rhs;
        return *this;
    }

    operator const_native_reference () const
    {
        return *_p;
    }

    /**
     * Casts to native container reference
     */
    operator native_reference ()
    {
        return *_p;
    }

    // *************************************************************************
    // BEGIN Requirements for container traits
    // Based on [C++ concepts: Container](http://en.cppreference.com/w/cpp/concept/Container)
    // *************************************************************************

    // *** ITERATORS ***
    //
    iterator begin ()
    {
        return _p->begin();
    }

    const_iterator begin () const
    {
        return _p->begin();
    }

    iterator end ()
    {
        return _p->end();
    }

    const_iterator end () const
    {
        return _p->end();
    }

#if __cplusplus >= 201103L
    const_iterator cbegin () const
    {
        return _p->cbegin();
    }

    const_iterator cend () const
    {
        return _p->cend();
    }
#else
    const_iterator cbegin () const
    {
        return _p->begin();
    }

    const_iterator cend () const
    {
        return _p->end();
    }
#endif

    // *** CAPACITY ***
    // 

    size_type size () const noexcept
    {
        return _p->size();
    }

    size_type max_size () const noexcept
    {
        return _p->max_size();
    }

    bool empty () const noexcept
    {
        return _p->empty();
    }

    // *** MODIFIERS ***
    //

    iterator erase (const_iterator pos)
    {
        return _p->erase(pos);
    }

    // FIXME
//    void swap (container & rhs)
//    {
//        _p->swap(*rhs._p);
//    }

    // *** NON-MEMBER FUNCTIONS (OPERATORS) ***
    //

    friend inline bool operator == (multimap_basic const & lhs
        , multimap_basic const & rhs)
    {
        return *lhs._p == *rhs._p;
    }

    friend inline bool operator != (multimap_basic const & lhs
        , multimap_basic const & rhs)
    {
        return *lhs._p != *rhs._p;
    }

    // *************************************************************************
    // } END Requirements for container traits
    // *************************************************************************

    // *************************************************************************
    // BEGIN Requirements for associative container traits {
    // *************************************************************************

    // *** LOOKUP ***
    //

    iterator find (key_type const & key)
    {
        return _p->find(key);
    }

    const_iterator find (key_type const & key) const
    {
        return _p->find(key);
    }

    // *** MODIFIERS
    //
    pfs::pair<iterator, bool> insert (key_type const & key, mapped_type const & value)
    {
        return pfs::make_pair(_p->insert(std::make_pair(key, value)), true);
    }

    // *************************************************************************
    // } END Requirements for associative container traits
    // *************************************************************************

    static mapped_type & mapped_reference (iterator it)
    {
        return it->second;
    }

    static mapped_type const & mapped_reference (const_iterator it)
    {
        return it->second;
    }
};

template <typename KvType>
class multimap : public multimap_basic<KvType, traits::container_value<KvType, multimap_wrapper> >
{
    typedef multimap_basic<KvType, traits::container_value<KvType, multimap_wrapper> > base_class;

public:
    typedef typename base_class::native_type            native_type;
    typedef typename base_class::native_reference       native_reference;
    typedef typename base_class::const_native_reference const_native_reference;
    
public:
    multimap ()
        : base_class()
    {}

    multimap (native_reference rhs)
        : base_class(rhs)
    {}

    multimap (const_native_reference rhs)
        : base_class(rhs)
    {}
};

template <typename KvType>
class multimap_reference : public multimap_basic<KvType, traits::container_reference<KvType, multimap_wrapper> >
{
    typedef multimap_basic<KvType, traits::container_reference<KvType, multimap_wrapper> > base_class;

public:
    typedef typename base_class::native_type            native_type;
    typedef typename base_class::native_reference       native_reference;
    typedef typename base_class::const_native_reference const_native_reference;
    
public:
    multimap_reference ()
        : base_class()
    {}

    multimap_reference (native_reference rhs)
        : base_class(rhs)
    {}

    multimap_reference (const_native_reference rhs)
        : base_class(rhs)
    {}
};

}} // pfs::stdcxx

#if __COMMENT__
namespace stdcxx {

template <typename Key, typename T>
struct multimap
{
    typedef std::multimap<Key, T> type;
};

} // stdcxx

namespace pfs {
namespace traits {

template <typename Key, typename T>
struct multimap_rep<Key, T, ::stdcxx::multimap> : public ::stdcxx::multimap<Key, T>::type
{
    typedef typename ::stdcxx::multimap<Key, T>::type    base_class;
    typedef typename ::stdcxx::multimap<Key, T>::type    native_type;

    typedef native_type const &                          const_native_reference;
    typedef typename native_type::size_type              size_type;
    typedef typename native_type::key_type               key_type;
    typedef typename native_type::mapped_type            mapped_type;
    typedef typename native_type::iterator               iterator;
    typedef typename native_type::const_iterator         const_iterator;
    typedef typename native_type::reverse_iterator       reverse_iterator;
    typedef typename native_type::const_reverse_iterator const_reverse_iterator;
    
	explicit multimap_rep ()
		: base_class()
	{}

    multimap_rep (const_native_reference rhs)
        : base_class(rhs)
    {}

    iterator erase (iterator position)
    {
#if __cplusplus >= 201103L
        return base_class::erase(position);
#else
        base_class::erase(position++);
        return position;
#endif        
    }

    iterator erase (iterator first, iterator last)
    {
#if __cplusplus >= 201103L
        return base_class::erase(first, last);
#else
        base_class::erase(first, last);
        return last;
#endif        
    }
};

}} // pfs::traits

#endif

#endif /* __PFS_TRAITS_STDCXX_MULTIMAP_HPP__ */
