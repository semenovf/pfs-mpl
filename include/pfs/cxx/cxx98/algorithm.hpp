/* 
 * File:   algorithm.hpp
 * Author: wladt
 *
 * Created on January 18, 2017, 1:18 PM
 */

#ifndef __PFS_CXX_CXX98_ALGORITHM_HPP__
#define __PFS_CXX_CXX98_ALGORITHM_HPP__

#include <algorithm>
#include <pfs/cxxlang.hpp>

namespace pfs {

template <typename T>
inline pfs_constexpr T const & min (const T & a, const T & b)
{
    return std::min(a, b);
}

template <typename T, typename Compare>
inline pfs_constexpr T const & min (T const & a, T const & b, Compare comp)
{
    return std::min(a, b, comp);
}

template <typename T>
inline pfs_constexpr T const & max (const T & a, const T & b)
{
    return std::max(a, b);
}

template <typename T, typename Compare>
inline pfs_constexpr T const & max (T const & a, T const & b, Compare comp)
{
    return std::max(a, b, comp);
}

template <typename InputIt, typename OutputIt>
inline OutputIt copy (InputIt first, InputIt last, OutputIt d_first)
{
    return std::copy(first, last, d_first);
}

template <typename RandomIt>
inline void sort (RandomIt first, RandomIt last)
{
    std::sort(first, last);
}

template <typename ForwardIt, typename T>
inline void replace (ForwardIt first
            , ForwardIt last
            , T const & old_value
            , T const & new_value)
{
    std::replace(first, last, old_value, new_value);
}

} // pfs

#endif /* __PFS_CXX_CXX98_ALGORITHM_HPP__ */
