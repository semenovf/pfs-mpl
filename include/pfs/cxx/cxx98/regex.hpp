#ifndef __PFS_CXX_CXX98_REGEX_HPP__
#define __PFS_CXX_CXX98_REGEX_HPP__

#include <pfs/config.h>

#if defined(HAVE_BOOST_REGEX)
#   include "regex_boost.hpp"
#elif defined(PFS_CC_MSC)
#   error "Implement for Win32"
#else
#   include "regex_custom.hpp"
#endif

#endif /* __PFS_CXX_CXX98_REGEX_HPP__ */

