#pragma once
#include <memory>
#include <pfs/cxxlang.hpp>

namespace pfs {

template <typename T>
using allocator = std::allocator<T>;

template< class T >
inline constexpr T * addressof (T & arg)
{
    return std::addressof(arg);
}

template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
using weak_ptr = std::weak_ptr<T>;

template <typename T, typename... Args>
inline shared_ptr<T> make_shared (Args... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename U>
inline shared_ptr<T> static_pointer_cast (shared_ptr<U> const & r) noexcept
{
    return std::static_pointer_cast<T,U>(r);
}

template <typename T, typename U>
inline shared_ptr<T> dynamic_pointer_cast (shared_ptr<U> const & r) noexcept
{
    return std::dynamic_pointer_cast<T,U>(r);
}

template <typename T, typename U>
inline shared_ptr<T> const_pointer_cast (shared_ptr<U> const & r) noexcept
{
    return std::const_pointer_cast<T,U>(r);
}

#if __cplusplus < 201703L

template <typename T, typename U>
inline shared_ptr<T> reinterpret_pointer_cast (shared_ptr<U> const & r)
{
    return shared_ptr<T>(r, reinterpret_cast<T*>(r.get()));
}

#endif


template <typename T, typename Deleter = std::default_delete<T> >
using unique_ptr = std::unique_ptr<T, Deleter>;

// see [std::make_unique](http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique)
// `Possible Implementation` section.
template<typename T, typename... Args>
inline unique_ptr<T> make_unique (Args &&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // pfs
