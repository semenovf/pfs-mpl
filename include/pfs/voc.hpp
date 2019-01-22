#pragma once
#include <pfs/type_traits.hpp>
#include <pfs/limits.hpp>
#include <pfs/string.hpp>
#include <pfs/compare.hpp>

namespace pfs {

/**
 */
template <typename StructEnumT>
class voc
{
#if __cplusplus < 201103L
    typedef typename size_type_n<sizeof(typename StructEnumT::value_enum)>::signed_type value_type;
    static const value_type bad_value ()
    {
        return numeric_limits<value_type>::max();
    }
#else
    // TODO for enum class
#endif
    
public:
    /**
     * @fn voc (voc const & other);
     * @brief Copy constructor.
     */

    /**
     * @fn voc & operator = (voc const & other);
     * @brief Copy assignable operator.
     */
    
#if __cplusplus < 201103L
    voc (typename StructEnumT::value_enum value = StructEnumT::__BAD_VALUE__)
        : _value(value)
    {}
#else
    // TODO for enum class
#endif

#if __cplusplus < 201103L
    voc & operator = (typename StructEnumT::value_enum value)
    {
        _value = value;
        return *this;
    }
#else
    // TODO for enum class
#endif

#if __cplusplus < 201103L
    typename StructEnumT::value_enum value () const
    {
        return _value;
    }
#else
    // TODO for enum class
#endif

    bool valid () const
    {
        return valid(_value);
    }

    static bool valid (int value);

private:
    value_type _value;
};

template <typename StructEnumT>
inline bool operator == (voc<StructEnumT> const & lhs, voc<StructEnumT> const & rhs)
{
    return lhs.value() == rhs.value();
}

#if __cplusplus < 201103L
template <typename StructEnumT>
inline bool operator == (voc<StructEnumT> const & lhs, typename StructEnumT::value_enum rhs)
{
    return lhs.value() == rhs;
}
#else
    // TODO for enum class
#endif

#if __cplusplus < 201103L
template <typename StructEnumT>
inline bool operator == (typename StructEnumT::value_enum lhs, voc<StructEnumT> const & rhs)
{
    return lhs == rhs.value();
}
#else
    // TODO for enum class
#endif

template <typename StructEnumT>
inline bool operator < (voc<StructEnumT> const & lhs, voc<StructEnumT> const & rhs)
{
    return lhs.value() < rhs.value();
}

#if __cplusplus < 201103L
template <typename StructEnumT>
inline bool operator < (voc<StructEnumT> const & lhs, typename StructEnumT::value_enum rhs)
{
    return lhs.value() < rhs;
}
#else
    // TODO for enum class
#endif

#if __cplusplus < 201103L
template <typename StructEnumT>
inline bool operator < (typename StructEnumT::value_enum lhs, voc<StructEnumT> const & rhs)
{
    return lhs < rhs.value();
}
#else
    // TODO for enum class
#endif

template <typename StructEnumT>
string to_string (voc<StructEnumT> const & voc);

template <typename StructEnumT>
string to_acronym (voc<StructEnumT> const & voc);

#if __cplusplus < 201103L
template <typename StructEnumT>
inline voc<StructEnumT> make_voc (int value)
{
    return voc<StructEnumT>::valid(value)
            ? voc<StructEnumT>(static_cast<typename StructEnumT::value_enum>(value))
            : voc<StructEnumT>();
}
#else
    // TODO for enum class
#endif

template <typename StructEnumT>
voc<StructEnumT> make_voc (string const & s);

template <typename StructEnumT>
string voc_name ();

} // namespace pfs

