#include "pfs/type_traits.hpp"
#include "pfs/filesystem/path.hpp"
#include "pfs/string.hpp"
#include "pfs/traits/stdcxx/string.hpp"

#if HAVE_QT_CORE
#   include "pfs/traits/qt/string.hpp"
#endif

namespace pfs {
namespace filesystem {

typedef string<stdcxx::string>           stdcxx_string_type;
//typedef string<stdcxx::string_reference> stdcxx_string_reference_type;

#if HAVE_QT_CORE

typedef string<qt::string>           qt_string_type;
//typedef string<qt::string_reference> qt_string_reference_type;

#endif

#if defined(_WIN32) && !defined(__CYGWIN__)
// Windows file system
// path::value_type is wchar_t

// FIXME
//template <>
//basic_path<details::path>::basic_path (stdcxx_string_type const & source/*, format fmt = auto_format*/)
//    : _d()
//{}

#   if HAVE_QT_CORE

template <>
basic_path<details::path>::basic_path (qt_string_type const & source/*, format fmt = auto_format*/)
    : base_class(source.native().toStdWString())
{}

#   endif

#else // Unix

template <>
path::path (stdcxx_string_type const & source/*, format fmt = auto_format*/)
    : base_class(source.native())
{}

#   if HAVE_QT_CORE

template <>
path::path (qt_string_type const & source/*, format fmt = auto_format*/)
    : base_class(source.native().toStdString())
{}

#   endif

#endif

}} // pfs::filesystem
