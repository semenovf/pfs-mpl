/* 
 * File:   algorithm.hpp
 * Author: wladt
 *
 * Created on January 18, 2017, 1:18 PM
 */

#ifndef __PFS_CXX11_ALGORITHM_HPP__
#define __PFS_CXX11_ALGORITHM_HPP__

#include <algorithm>

namespace pfs {

template <typename T>
inline T const & min (T const & a, T const & b )
{
    return std::min(a, b);
}

template <typename T, typename Compare>
inline T const & min (T const & a, T const & b, Compare comp)
{
    return std::min(a, b, comp);
}

template <typename T>
inline T const & max (T const & a, T const & b )
{
    return std::max(a, b);
}

template <typename T, typename Compare>
inline T const & max (T const & a, T const & b, Compare comp)
{
    return std::max(a, b, comp);
}

template <typename InputIt, typename OutputIt>
inline OutputIt copy (InputIt first, InputIt last, OutputIt d_first)
{
    return std::copy(first, last, d_first);
}

} // pfs

#endif /* __PFS_CXX11_ALGORITHM_HPP__ */
