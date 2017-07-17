
/* 
 * File:   ctype.hpp
 * Author: wladt
 *
 * Created on July 6, 2017, 11:32 AM
 */

#ifndef __PFS_CTYPE_HPP__
#define __PFS_CTYPE_HPP__

namespace pfs {

template <typename CharT>
bool is_alnum (CharT c);

template <typename CharT>
bool is_alpha (CharT c);

template <typename CharT>
bool is_cntrl (CharT c);

template <typename CharT>
bool is_digit (CharT c);

template <typename CharT>
bool is_graph (CharT c);

template <typename CharT>
bool is_lower (CharT c);

template <typename CharT>
bool is_print (CharT c);

template <typename CharT>
bool is_punct (CharT c);

template <typename CharT>
bool is_space (CharT c);

template <typename CharT>
bool is_upper (CharT c);

template <typename CharT>
bool is_xdigit (CharT c);

template <typename CharT>
char to_ascii (CharT c);

template <>
inline char to_ascii<char> (char c)
{
    return c >= 0 && c <= 127 
            ? c
            : -1;
}

} // pfs

#include <pfs/compiler.hpp>
#include PFS_CC_HEADER(ctype)

#endif /* __PFS_CTYPE_HPP__ */
