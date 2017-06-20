/* 
 * File:   string.hpp
 * Author: wladt
 *
 * Created on January 9, 2017, 3:21 PM
 */

#ifndef __PFS_TRAITS_STDCXX_STRING_HPP__
#define __PFS_TRAITS_STDCXX_STRING_HPP__

#include <string>
#include <pfs/iterator.hpp>
#include <pfs/cxxlang.hpp>
#include <pfs/traits/string_value_ref.hpp>

namespace pfs {
namespace traits {
namespace stdcxx {

template <typename ValueOrReference>
class basic_string
{
    typedef ValueOrReference internal_type;

public:
    typedef basic_string<typename internal_type::string_value_type>     string_value_type;
    typedef basic_string<typename internal_type::string_reference_type> string_reference_type;

    typedef typename internal_type::native_type            native_type;
    typedef typename internal_type::native_reference       native_reference;
    typedef typename internal_type::const_native_reference const_native_reference;
    
    typedef typename native_type::value_type       value_type;
    typedef typename native_type::const_pointer    const_pointer;
    typedef typename native_type::reference        reference;
    typedef typename native_type::const_reference  const_reference;
    typedef typename native_type::iterator         iterator;
    typedef typename native_type::const_iterator   const_iterator;
    typedef typename native_type::reverse_iterator reverse_iterator;
    typedef typename native_type::const_reverse_iterator const_reverse_iterator;
    typedef typename native_type::difference_type  difference_type;
    typedef typename native_type::size_type        size_type;

protected:
    internal_type _p;
    
public:
    basic_string ()
    {}

    basic_string (native_reference rhs)
        : _p(rhs)
    {}

    basic_string (const_native_reference rhs)
        : _p(rhs)
    {}
    
    basic_string (const_pointer s)
        : _p(s)
    {}

    template <typename InputIt>
    basic_string (InputIt first, InputIt last)
        : _p(first, last)
    {}
    
    basic_string & operator = (native_reference rhs)
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
    
    size_type size () const
    {
        return _p->size();
    }
    
    size_type max_size () const
    {
        return _p->max_size();
    }
    
    const_pointer data () const
    {
        return _p->data();
    }
    
    const_iterator begin () const
    {
        return _p->begin();
    }

    const_iterator end () const
    {
        return _p->end();
    }

    const_reverse_iterator rbegin () const
    {
        return _p->rbegin();
    }

    const_reverse_iterator rend () const
    {
        return _p->rend();
    }

    value_type at (size_type pos) const
    {
        return _p->at(pos);
    }

    int compare (size_type pos1, size_type count1
            , basic_string const & rhs, size_type pos2, size_type count2) const
    {
        return _p->compare(pos1, count1, rhs._p, pos2, count2) ;
    }
    
    iterator erase (const_iterator first, const_iterator last)
    {
#if __cplusplus >= 201103L
        return native_type::erase(first, last);
#else
        //
        // C++ prior to C++11 
        // erase() has signature `iterator erase(iterator first, iterator last)`
        //
        const_iterator begin = _p->begin();
        size_type index = pfs::distance(begin, first);
        size_type count = pfs::distance(first, last);
        native_type::erase(index, count);
        return _p->begin() + index;
#endif
    }
    
    friend inline bool operator == (basic_string const & lhs, basic_string const & rhs)
    {
        return *lhs._p == *rhs._p;
    }

    friend inline bool operator != (basic_string const & lhs, basic_string const & rhs)
    {
        return *lhs._p != *rhs._p;
    }

    friend inline bool operator < (basic_string const & lhs, basic_string const & rhs)
    {
        return *lhs._p < *rhs._p;
    }

    friend inline bool operator <= (basic_string const & lhs, basic_string const & rhs)
    {
        return *lhs._p <= *rhs._p;
    }

    friend inline bool operator > (basic_string const & lhs, basic_string const & rhs)
    {
        return *lhs._p > *rhs._p;
    }

    friend inline bool operator >= (basic_string const & lhs, basic_string const & rhs)
    {
        return *lhs._p >= *rhs._p;
    }
};

typedef basic_string<string_value<char, std::string> >     string;
typedef basic_string<string_value<wchar_t, std::wstring> > wstring;
typedef basic_string<string_ref<char, std::string> >       string_reference;
typedef basic_string<string_ref<wchar_t, std::wstring> >   wstring_reference;

#if __cplusplus >= 201103L
typedef basic_string<string_value<char16_t, std::u16string> > u16string;
typedef basic_string<string_value<char32_t, std::u32string> > u32string;
typedef basic_string<string_ref<char16_t, std::u16string> >   u16string_reference;
typedef basic_string<string_ref<char32_t, std::u32string> >   u32string_reference;
#endif

}}} // pfs::traits::stdcxx

#if __OBSOLETE__

template <>
class c_str<std::string> 
    : public traits::stdcxx::c_str<std::string>
{
    typedef traits::stdcxx::c_str<std::string> base_type;
public:
    explicit c_str (string_type const & s)
        : base_type(s)
    {}
};

template <>
class c_wstr<std::wstring> 
    : public traits::stdcxx::c_str<std::wstring>
{
    typedef traits::stdcxx::c_str<std::wstring> base_type;
public:
    explicit c_wstr (string_type const & s)
        : base_type(s)
    {}
};

#endif

#endif /* __PFS_TRAITS_STDCXX_STRING_HPP__ */