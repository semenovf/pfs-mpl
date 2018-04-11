#pragma once
#include <pfs/v2/byte_string.hpp>

namespace pfs {

class byte_istream
{
public:
    byte_istream (byte_string::const_iterator begin
            , byte_string::const_iterator end
            , endian const & order = endian::native_order())
        : b (begin)
        , e (end)
        , o (order)
    {}

    byte_string::const_iterator begin () const
    {
        return b;
    }

    byte_string::const_iterator end () const
    {
        return e;
    }

    byte_string::const_iterator cbegin () const
    {
        return b;
    }

    byte_string::const_iterator cend () const
    {
        return e;
    }

    endian const & order () const
    {
        return o;
    }

    byte_string::difference_type available () const
    {
        return pfs::distance(b, e);
    }

    void skip (size_t n)
    {
        n = pfs::min(n, integral_cast_check<size_t>(available()));
        pfs::advance(b, n);
    }

    // TODO DEPRECATED
    template <typename IntegerType>
    void read_integral (IntegerType & v)
    {
        read_integer<IntegerType>(v);
    }

    template <typename IntegerType>
    void read_integer (IntegerType & v)
    {
        union u
        {
            IntegerType const v;
            byte_string::value_type const b[sizeof (IntegerType)];
        };

        byte_string::const_iterator pos(b);
        pfs::advance(pos, sizeof (IntegerType));

        if (pos <= e) {
            u const * d = reinterpret_cast<u const *> (b.base());
            v = o.convert(d->v);
            b = pos;
        } else {
            throw io_exception(make_error_code(io_errc::stream), NOT_ENOUGH_DATA_EXCEPTION_STR);
        }
    }

    template <typename Real>
    void read_real (Real & v)
    {
        union u
        {
            Real const v;
            byte_string::value_type const b[sizeof (Real)];
        };

#ifdef PFS_HAVE_INT64
        if (sizeof (Real) == 8) {
            uint64_t d = 0;
            read_integral(d);
            v = *reinterpret_cast<Real *> (& d);
        } else
#endif
            if (sizeof (Real) == 4) {
            uint32_t d = 0;
            read_integral(d);
            v = *reinterpret_cast<Real *> (& d);
        } else if (sizeof (Real) == 2) {
            uint16_t d = 0;
            read_integral(d);
            v = *reinterpret_cast<Real *> (& d);
        } else {
            // FIXME
            //        byte_string::const_iterator pos(ctx.b);
            //        std::advance(pos, sizeof(Float));
            //
            //        if (pos <= ctx.e) {
            //            u * b = reinterpret_cast<u *>(ctx.b.base());
            //
            //            if (order != endian::native_order()) {
            //                byte_string::value_type b[sizeof(Float)];
            //
            //            for (int i = 0, j = sizeof(Float) - 1; j >= 0; ++i, --j) {
            //                b[i] = d.b[j];
            //            }
            //
            //            appender.append(byte_string(b, sizeof(Float)));
            //        } else {
            //            appender.append(byte_string(d.b, sizeof(Float)));
            //        }
            //
            //            v = ctx.o.convert(d->v);
            //            ctx.b = pos;
            //            ctx.fail = false;
            //        } else {
            //            ctx.fail = true;
            //        }
        }
    }

    void read (byte_string & v, byte_string::size_type sz)
    {
        if (static_cast<byte_string::size_type>(pfs::distance(b, e)) < sz)
            throw io_exception(make_error_code(io_errc::stream), NOT_ENOUGH_DATA_EXCEPTION_STR);

        byte_string::const_iterator last(b);
        pfs::advance(last, sz);
        v.append(b, last);
        b = last;
    }

    void read (byte_string::pointer v, byte_string::size_type sz)
    {
        if (static_cast<byte_string::size_type> (pfs::distance(b, e)) < sz)
            throw io_exception(make_error_code(io_errc::stream), NOT_ENOUGH_DATA_EXCEPTION_STR);
        pfs::copy(b.base(), b.base() + sz, v);
        pfs::advance(b, sz);
    }

    void read (char * v, byte_string::size_type sz)
    {
        read(reinterpret_cast<byte_string::pointer> (v), sz);
    }

    void read_tail (byte_string & v)
    {
        v.append(b, e);
        b = e;
    }

private:
    byte_string::const_iterator b;
    byte_string::const_iterator e;
    endian o;
};

template <int N>
byte_istream & operator >> (byte_istream & is, byte_string_ref_n<N> const & v)
{
    typename byte_string_ref_n<N>::size_type sz = 0;
    is >> sz;
    is.read(*v.p, sz);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, byte_string_ref const & v)
{
    is.read(*v.p, v.max_size);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, buffer_wrapper<byte_string::value_type> const & v)
{
    is.read(v.p, v.max_size);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, buffer_wrapper<char> const & v)
{
    is.read(v.p, v.max_size);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, bool & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, char & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, signed char & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, unsigned char & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, wchar_t & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, short & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, unsigned short & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, int & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, unsigned int & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, long & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, unsigned long & v)
{
    is.read_integral(v);
    return is;
}

#if PFS_HAVE_LONGLONG

inline byte_istream & operator >> (byte_istream & is, long long & v)
{
    is.read_integral(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, unsigned long long & v)
{
    is.read_integral(v);
    return is;
}

#endif

inline byte_istream & operator >> (byte_istream & is, float & v)
{
    is.read_real(v);
    return is;
}

inline byte_istream & operator >> (byte_istream & is, double & v)
{
    is.read_real(v);
    return is;
}

} // pfs