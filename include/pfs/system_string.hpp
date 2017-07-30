
/* 
 * File:   string.hpp
 * Author: wladt
 *
 * Created on July 4, 2017, 9:53 AM
 */

#ifndef __PFS_SYSTEM_STRING_HPP__
#define __PFS_SYSTEM_STRING_HPP__

#include <pfs/compiler.hpp>
#include <pfs/string.hpp>

#if PFS_CC_MSC
#   include <pfs/traits/stdcxx/string.hpp>
    namespace pfs {
        typedef string<traits::stdcxx::wstring>           system_string;
        typedef string<traits::stdcxx::wstring_reference> system_string_reference;
    } // pfs
#   define PFS_LITERAL(s) L##s
#   define PFS_SPRINTF swprintf
#else
#   include <pfs/traits/stdcxx/string.hpp>
    namespace pfs {
        typedef string<traits::stdcxx::string>           system_string;
        typedef string<traits::stdcxx::string_reference> system_string_reference;
    } // pfs        
#   define PFS_LITERAL(s) s
#   define PFS_SPRINTF sprintf
#endif

namespace pfs {

typedef system_string::code_unit_type system_char_t;

} // pfs
    
#endif /* __PFS_SYSTEM_STRING_HPP__ */

