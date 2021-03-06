#pragma once

#if HAVE_MPARK_VARIANT
#include <pfs/../../3rdparty/variant/include/mpark/variant.hpp>
#include <pfs/type_traits.hpp>

namespace pfs {

constexpr std::size_t variant_npos = mpark::variant_npos;

using in_place_t = mpark::in_place_t;

template <std::size_t I>
using in_place_index_t = mpark::in_place_index_t<I>;

template <typename T>
using in_place_type_t = mpark::in_place_type_t<T>;

template <typename... Types>
using variant = mpark::variant<Types...>;

template <size_t I, typename T>
using variant_alternative_t = mpark::variant_alternative_t<I, T>;

// There is no such function in C++17
/*
template <std::size_t I, typename... Ts>
inline constexpr bool holds_alternative (variant<Ts...> const & v) noexcept
{
    return mpark::holds_alternative<I, Ts...>(v);
}
*/

template <typename T, typename... Ts>
inline constexpr bool holds_alternative (variant<Ts...> const & v) noexcept
{
    return mpark::holds_alternative<T, Ts...>(v);
}

template <std::size_t I, typename... Types>
constexpr variant_alternative_t<I, variant<Types...>> & get (variant<Types...> & v)
{
    return mpark::get<I, Types...>(v);
}

template <std::size_t I, typename... Types>
constexpr variant_alternative_t<I, variant<Types...>> && get (variant<Types...> && v)
{
    return mpark::get<I, Types...>(std::forward<variant<Types...>>(v));
}

template <std::size_t I, typename... Types>
constexpr variant_alternative_t<I, variant<Types...>> const & get (variant<Types...> const & v)
{
    return mpark::get<I, Types...>(v);
}

template <std::size_t I, typename... Types>
constexpr variant_alternative_t<I, variant<Types...>> const && get (variant<Types...> const && v)
{
    return mpark::get<I, Types...>(std::forward<variant<Types...>>(v));
}

template <typename T, typename... Types>
constexpr T & get (variant<Types...>& v)
{
    return mpark::get<T, Types...>(v);
}

template <typename T, typename... Types>
constexpr T && get (variant<Types...> && v)
{
    return mpark::get<T, Types...>(std::forward<variant<Types...>>(v));
}

template <typename T, typename... Types>
constexpr const T & get (variant<Types...> const & v)
{
    return mpark::get<T, Types...>(v);
}

template <typename T, typename... Types>
constexpr const T && get (variant<Types...> const && v)
{
    return mpark::get<T, Types...>(std::forward<variant<Types...>>(v));
}

template <std::size_t I, typename... Types>
constexpr add_pointer_t<variant_alternative_t<I, variant<Types...>>>
    get_if (variant<Types...> * pv) noexcept
{
    return mpark::get_if<I, Types...>(pv);
}

template <std::size_t I, typename... Types>
constexpr add_pointer_t<const variant_alternative_t<I, variant<Types...>>>
    get_if (variant<Types...> const * pv) noexcept
{
    return mpark::get_if<I, Types...>(pv);
}

template <typename T, typename... Types>
constexpr add_pointer_t<T> get_if (variant<Types...> * pv) noexcept
{
    return mpark::get_if<T, Types...>(pv);
}

template <typename T, typename... Types>
constexpr add_pointer_t<const T> get_if (variant<Types...> const * pv) noexcept
{
    return mpark::get_if<T, Types...>(pv);
}

template <typename Visitor, typename... Variants>
#ifdef MPARK_CPP14_CONSTEXPR
inline constexpr decltype(auto) visit (Visitor && visitor, Variants &&... vars)
#else
inline constexpr auto visit (Visitor && visitor, Variants &&... vars)
    -> decltype(mpark::visit<Visitor, Variants...>(std::forward<Visitor>(visitor)
            , std::forward<Variants>(vars)...))
#endif
{
    return mpark::visit<Visitor, Variants...>(std::forward<Visitor>(visitor)
            , std::forward<Variants>(vars)...);
}

} // pfs

#else

#include <pfs/cxx/cxx98/variant.hpp>

#endif
