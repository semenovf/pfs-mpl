/* 
 * File:   iterator.hpp
 * Author: wladt
 *
 * Created on December 30, 2016, 11:00 AM
 */

#ifndef __PFS_CXX98_ITERATOR_HPP__
#define __PFS_CXX98_ITERATOR_HPP__

#include <iterator>
#include <pfs/types.hpp>

namespace pfs {

typedef std::input_iterator_tag         input_iterator_tag;
typedef std::output_iterator_tag        output_iterator_tag;
typedef std::forward_iterator_tag       forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

template <typename Category, typename T, typename Distance = ptrdiff_t,
    typename Pointer = T *, typename Reference = T &>
struct iterator
{
    typedef Category  iterator_category;
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
};

template <typename Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
};

template <typename T>
struct iterator_traits <T *>
{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T         value_type;
    typedef ptrdiff_t difference_type;
    typedef T *       pointer;
    typedef T &       reference;
};

template <typename T>
struct iterator_traits<const T *>
{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T         value_type;
    typedef ptrdiff_t difference_type;
    typedef const T * pointer;
    typedef const T & reference;
};

template <typename Category
        , typename Derived
        , typename T
        , typename Pointer
        , typename Reference
        , typename Distance = ptrdiff_t>
struct iterator_facade; 

template <typename Derived
        , typename T
        , typename Pointer
        , typename Reference
        , typename Distance>
struct iterator_facade<input_iterator_tag, Derived, T, Pointer, Reference, Distance> 
{
    typedef input_iterator_tag iterator_category;
    typedef T                  value_type;
    typedef Distance           difference_type;
    typedef Pointer            pointer;
    typedef Reference          reference;

    static reference ref (Derived &);
    static pointer   ptr (Derived &);
    static void      increment (Derived &, difference_type n = 1);
    static bool      equals (Derived const & lhs, Derived const & rhs);

    value_type operator * () const
    {
    	return Derived::ref(*const_cast<Derived *>(static_cast<Derived const *>(this)));
    }

    pointer operator -> () const
    {
    	return Derived::ptr(*const_cast<Derived *>(static_cast<Derived const *>(this)));
    }

    Derived & operator ++ () // prefix increment
	{
    	Derived::increment(static_cast<Derived &>(*this), 1);
    	return static_cast<Derived &>(*this);
	}

    Derived operator ++ (int) // postfix increment
	{
        Derived r(static_cast<Derived &>(*this));
        Derived::increment(static_cast<Derived &>(*this), 1);
		return r;
	}
    
    friend bool operator == (Derived const & lhs, Derived const & rhs)
    {
        return Derived::equals(lhs, rhs);
    }

    friend bool operator != (Derived const & lhs, Derived const & rhs)
    {
        return ! Derived::equals(lhs, rhs);
    }
};

template <typename Derived
        , typename T
        , typename Pointer
        , typename Reference
        , typename Distance>
struct iterator_facade<output_iterator_tag, Derived, T, Pointer, Reference, Distance> 
{
    typedef output_iterator_tag iterator_category;
    typedef T                   value_type;
    typedef Distance            difference_type;
    typedef Pointer             pointer;
    typedef Reference           reference;

    static reference ref (Derived &);
    static void increment (Derived &, difference_type n = 1);

    reference operator * () const
    {
    	return Derived::ref(*const_cast<Derived *>(static_cast<Derived const *>(this)));
    }
    
    Derived & operator ++ () // prefix increment
	{
    	Derived::increment(static_cast<Derived &>(*this), 1);
    	return static_cast<Derived &>(*this);
	}

    Derived operator ++ (int) // postfix increment
	{
        Derived r(static_cast<Derived &>(*this));
        Derived::increment(static_cast<Derived &>(*this), 1);
		return r;
	}
};

template <typename Derived
        , typename T
        , typename Pointer
        , typename Reference
        , typename Distance>
struct iterator_facade<forward_iterator_tag, Derived, T, Pointer, Reference, Distance>
        : public iterator_facade<input_iterator_tag, Derived, T, Pointer, Reference, Distance>
{
    typedef forward_iterator_tag iterator_category;
    typedef Reference            reference;
    typedef const Reference      const_reference;
    
    reference operator * ()
    {
    	return Derived::ref(*static_cast<Derived *>(this));
    }

    const_reference operator * () const
    {
    	return Derived::ref(*static_cast<Derived const *>(this));
    }
};

template <typename Derived
        , typename T
        , typename Pointer
        , typename Reference
        , typename Distance>
struct iterator_facade<bidirectional_iterator_tag, Derived, T, Pointer, Reference, Distance>
        : public iterator_facade<forward_iterator_tag, Derived, T, Pointer, Reference, Distance>
{
    typedef bidirectional_iterator_tag iterator_category;
    typedef Distance difference_type;
    
    static void decrement (Derived &, difference_type n);

    Derived & operator -- () // prefix decrement
	{
    	Derived::decrement(static_cast<Derived &>(*this), 1);
    	return static_cast<Derived &>(*this);
	}

    Derived operator -- (int) // postfix decrement
	{
        Derived r(static_cast<Derived &>(*this));
        Derived::decrement(static_cast<Derived &>(*this), 1);
		return r;
	}
};

template <typename Derived
        , typename T
        , typename Pointer
        , typename Reference
        , typename Distance>
struct iterator_facade<random_access_iterator_tag, Derived, T, Pointer, Reference, Distance>
        : public iterator_facade<bidirectional_iterator_tag, Derived, T, Pointer, Reference, Distance>
{
    typedef random_access_iterator_tag iterator_category;
    typedef Distance     difference_type;
    typedef Reference    reference;

    static reference subscript (Derived &, difference_type n);
    static difference_type diff (Derived const & lhs, Derived const & rhs);
    static int compare (Derived const & lhs, Derived const & rhs);
    
    static bool equals (Derived const & lhs, Derived const & rhs)
    {
        return Derived::compare(lhs, rhs) == 0;
    }
    
  	Derived & operator += (difference_type n)
	{
        Derived::increment(static_cast<Derived &>(*this), n);
    	return static_cast<Derived &>(*this);
	}

   	Derived & operator -= (difference_type n)
	{
        Derived::decrement(static_cast<Derived &>(*this), n);
    	return static_cast<Derived &>(*this);
	}

   	reference operator [] (difference_type index)
	{
		return Derived::subscript(static_cast<Derived &>(*this), index);
	}

    friend Derived operator + (Derived const & lhs, difference_type n)
    {
        Derived r(lhs);
        Derived::increment(r, n);
        return r;
    }

    friend Derived operator + (difference_type n, Derived const & rhs)
    {
        return operator + (rhs, n);
    }

    friend Derived operator - (Derived const & lhs, difference_type n)
    {
        Derived r(lhs);
        Derived::decrement(r, n);
        return r;
    }

    friend difference_type operator - (Derived const & lhs, Derived const & rhs)
    {
        return Derived::diff(lhs, rhs);
    }

    friend bool operator < (Derived const & lhs, Derived const & rhs)
    {
        return Derived::compare(lhs, rhs) < 0;
    }

    friend bool operator > (Derived const & lhs, Derived const & rhs)
    {
        return Derived::compare(lhs, rhs) > 0;
    }

    friend bool operator <= (Derived const & lhs, Derived const & rhs)
    {
        return Derived::compare(lhs, rhs) <= 0;
    }

    friend bool operator >= (Derived const & lhs, Derived const & rhs)
    {
        return Derived::compare(lhs, rhs) >= 0;
    }
};

template <typename InputIt>
inline typename pfs::iterator_traits<InputIt>::difference_type
distance (InputIt begin, InputIt end)
{
    return std::distance(begin, end);
}

template <typename InputIt>
inline void
advance (InputIt & it, typename pfs::iterator_traits<InputIt>::difference_type n)
{
    return std::advance(it, n);
}

#if __cplusplus < 201103L

template <typename Container>
inline std::back_insert_iterator<Container> 
back_inserter (Container & c)
{
    return std::back_insert_iterator<Container>(c);
}

#endif

} // pfs

#endif /* __PFS_CXX98_ITERATOR_HPP__ */
