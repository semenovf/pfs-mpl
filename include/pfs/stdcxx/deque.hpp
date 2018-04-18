#pragma once
#include <deque>

namespace pfs {

namespace stdcxx {

template <typename T, typename DerivedT>
class deque : public std::deque<T>
{
    typedef std::deque<T> base_class;

public:
    typedef typename base_class::value_type       value_type;
    typedef typename base_class::size_type        size_type;
    typedef typename base_class::difference_type  difference_type;
    typedef typename base_class::reference        reference;
    typedef typename base_class::const_reference  const_reference;
    typedef typename base_class::pointer          pointer;
    typedef typename base_class::const_pointer    const_pointer;
    typedef typename base_class::iterator         iterator;
    typedef typename base_class::const_iterator   const_iterator;
    typedef typename base_class::reverse_iterator reverse_iterator;
    typedef typename base_class::const_reverse_iterator const_reverse_iterator;

    inline iterator const_cast_iterator (const_iterator it)
    {
        iterator result(this->begin());
        std::advance(result, std::distance(this->cbegin(), it));
        return result;
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    // Constructors                                                          //
    ///////////////////////////////////////////////////////////////////////////

    deque () : base_class() {}

    deque (size_type count, const_reference value)
        : base_class(count, value)
    {}

    explicit deque (size_type count)
        : base_class(count)
    {}

    template <typename InputIt>
    deque (InputIt first, InputIt last)
        : base_class(first, last)
    {}

    deque (deque const & rhs)
        : base_class(rhs)
    {}

#if __cplusplus >= 201103L
    deque (deque && rhs)
        : base_class(std::forward<deque>(rhs))
    {}

    deque (std::initializer_list<T> ilist)
        : base_class(ilist.begin(), ilist.end())
    {}
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Assign operators and methods                                          //
    ///////////////////////////////////////////////////////////////////////////

    DerivedT & operator = (DerivedT const & rhs)
    {
        base_class::operator = (rhs);
        return *this;
    }

#if __cplusplus >= 201103L
    DerivedT & operator = (DerivedT && rhs)
    {
        base_class::operator = (std::forward<deque>(rhs));
        return *this;
    }

    DerivedT & operator = (std::initializer_list<T> ilist)
    {
        base_class::operator = (ilist);
        return *this;
    }
#endif

    DerivedT & assign (size_type count, const_reference value)
    {
        base_class::assign(count, value);
        return *this;
    }

    template <typename InputIt>
    DerivedT & assign (InputIt first, InputIt last)
    {
        base_class::template assign<InputIt>(first, last);
        return *this;
    }

#if __cplusplus >= 201103L
    DerivedT & assign (std::initializer_list<T> ilist)
    {
        base_class::assign(ilist);
        return *this;
    }
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Element access                                                        //
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @fn reference at (size_type pos)
     */

    /**
     * @fn const_reference at (size_type pos) const
     */

    /**
     * @fn reference operator [] (size_type pos)
     */

    /**
     * @fn const_reference operator [] (size_type pos) const
     */

    /**
     * @fn reference front ()
     */

    /**
     * @fn const_reference front () const
     */

    /**
     * @fn reference back ()
     */

    /**
     * @fn const_reference back () const
     */

    ///////////////////////////////////////////////////////////////////////////
    // Iterators                                                             //
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @fn iterator begin ()
     */

    /**
     * @fn const_iterator begin () const
     */

#if __cplusplus < 201103L
    const_iterator cbegin () const
    {
        return this->begin();
    }
#endif

    /**
     * @fn iterator end ()
     */

    /**
     * @fn const_iterator end () const
     */

#if __cplusplus < 201103L
    const_iterator cend () const
    {
        return this->end();
    }
#endif

    /**
     * @fn iterator rbegin ()
     */

    /**
     * @fn const_iterator rbegin () const
     */

#if __cplusplus < 201103L
    const_iterator crbegin () const
    {
        return this->rbegin();
    }
#endif

    /**
     * @fn iterator rend ()
     */

    /**
     * @fn const_iterator rend () const
     */

#if __cplusplus < 201103L
    const_iterator crend () const
    {
        return this->rend();
    }
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Capacity                                                              //
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @fn bool empty () const
     */

    /**
     * @fn size_type size () const
     */

    /**
     * @fn size_type max_size () const
     */

#if __cplusplus < 201103L
    // @note Result may not be the same as for C++11 version
    void shrink_to_fit ()
    {
        if (this->capacity() > this->size()) {
            this->reserve(0);
        }
    }
#endif

    ///////////////////////////////////////////////////////////////////////////
    // Modifiers                                                             //
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @fn void clear ()
     */

    /**
     * @fn iterator insert (const_iterator pos, T const & value)
     */

#if __cplusplus < 201103L
    iterator insert (const_iterator pos, T const & value)
    {
        return base_class::erase(const_cast_iterator(pos), value);
    }
#endif

#if __cplusplus >= 201103L
    /**
     * @fn iterator insert (const_iterator pos, T && value)
     */
#endif

    /**
     * @fn iterator insert (const_iterator pos, size_type count, T const & value)
     *
     * @return Iterator pointing to the first element inserted, or @a pos if count==0.
     */

    /**
     * @fn template <typename InputIt>
     *     iterator insert (const_iterator pos, InputIt first, InputIt last)
     */

#if __cplusplus < 201103L
    iterator insert (const_iterator pos, size_type count, const_reference value)
    {
        //
        // C++ <  C++11: void insert (iterator pos, size_type count, const T & value);
        // C++ >= C++11: iterator insert (const_iterator pos, size_type count, const T & value);
        //
        // Note: All iterators are invalidated.
        //
        iterator result = pos;

        if (count > 0) {
            result = this->insert(pos, value); //  first inserted value
            difference_type i = std::distance(this->cbegin(), result);

            if (--count > 0) {
                base_class::insert(const_cast_iterator(pos), count, value);
                result = this->begin();
                std::advance(result, i);
            }
        }
        return result;
    }

    template <typename InputIt>
    iterator insert (const_iterator pos, InputIt first, InputIt last)
    {
        return base_class::template insert<InputIt>(
                const_cast_iterator(pos), first, last);
    }
#endif

#if __cplusplus >= 201103L
    /**
     * @fn iterator insert (const_iterator pos, std::initializer_list<T> ilist)
     */
#endif

#if __cplusplus >= 201103L
    /**
     * @fn template <typename... Args>
     *     iterator emplace (const_iterator pos, Args &&... args)
     */
#endif

    /**
     * @fn iterator erase (const_iterator pos)
     */

    /**
     * @fn iterator erase (const_iterator first, const_iterator last)
     */

#if __cplusplus < 201103L
    //
    // C++98 has erase() methods signatures like this once:
    //      iterator erase(iterator pos)
    //      iterator erase(iterator first, iterator last)
    //

    inline iterator erase (const_iterator pos)
    {
        return base_class::erase(const_cast_iterator(pos));
    }

    inline iterator erase (const_iterator first, const_iterator last)
    {
        return base_class::erase(const_cast_iterator(first)
                , const_cast_iterator(last));
    }
#endif

    /**
     * @fn void push_back (const_reference value)
     */

#if __cplusplus >= 201103L
    /**
     * @fn void push_back (T && value)
     */
#endif

#if __cplusplus >= 201103L
    // TODO Implement to meet C++17:
    // reference emplace_back (Args &&... args)
    //

    /**
     * @fn template <typename... Args>
     *     void emplace_back (Args &&... args)
     */

    /**
     * @fn template <typename... Args>
     *     void emplace_front (Args &&... args )
     */
#endif

    /**
     * @fn void pop_back ()
     */

    /**
    * @fn void push_front (const_reference value)
    */

#if __cplusplus >= 201103L
    /**
    * @fn void push_front (T && value)
    */
#endif

    /**
     * @fn void pop_front ()
     */

    void resize (size_type count)
    {
        base_class::resize(count, T());
    }

    void resize (size_type count, const_reference value)
    {
        base_class::resize(count, value);
    }

    /**
     * @fn void swap (deque & rhs)
     */

    ///////////////////////////////////////////////////////////////////////////
    // Compare operators                                                     //
    ///////////////////////////////////////////////////////////////////////////
//     template <typename T>
//     friend inline bool operator == (DerivedT const & lhs, DerivedT const & rhs )
//     {
//     }
};

}} // pfs::stdcxx