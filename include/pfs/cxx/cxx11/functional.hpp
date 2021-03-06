#pragma once
#include <functional>

using namespace std::placeholders;

namespace pfs {

template <typename T>
using reference_wrapper = std::reference_wrapper<T>;

template <typename T>
inline reference_wrapper<T> ref (T & t) noexcept
{
    return std::ref<T>(t);
}

template <typename T>
reference_wrapper<const T> cref (T const & t) noexcept
{
    return std::cref<T>(t);
}

///////////////////////////////////////////////////////////////////////////////
// bind                                                                      //
///////////////////////////////////////////////////////////////////////////////

using std::bind;

///////////////////////////////////////////////////////////////////////////////
// function                                                                  //
///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
using function = std::function<Args...>;

template <typename T = void>
using greater = std::greater<T>;

template <typename T = void>
using less = std::less<T>;

} // pfs
