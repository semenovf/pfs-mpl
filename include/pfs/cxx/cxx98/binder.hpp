/* AUTOMATICALLY GENERATED BY './binder_gen.pl' */
/*
 * binder.hpp
 *
 *  Created on: 2017-06-16 15:47:32
 *      Author: wladt
 */

#ifndef __PFS_BINDER_HPP__
#define __PFS_BINDER_HPP__

namespace pfs {

template <typename T>
struct binder_type_trait { typedef T type; };

template <typename T>
struct binder_type_trait<const T &> { typedef T type; };

template <typename ReturnType>
class binder_base
{
public:
    typedef ReturnType return_type;

protected:
    size_t _size;

    binder_base (size_t size)
        : _size(size)
    {}

//    virtual void * placement_copy (void * ptr) const = 0;

public:
    virtual ~binder_base () {}

    size_t size () const
    {
        return _size;
    }

    virtual return_type operator () () const = 0;

//    void * pcopy (void * ptr)
//    {
//        return placement_copy(ptr);
//    }

//    static void * move (void * dest, void * src, size_t n);
};

//template <typename ReturnType>
//void * binder_base<ReturnType>::move (void * dest, void * src, size_t n)
//{
//    void * p = dest;
//
//    while (n) {
//        binder_base * bb = static_cast<binder_base *>(src);
//
//        PFS_ASSERT(n >= bb->size());
//        n -= bb->size();
//        src = static_cast<char *>(src) + bb->size();
//
//        p = bb->pcopy(p);
//        bb->~binder_base();
//    }
//
//    return dest;
//}

template <typename ReturnType>
class binder_function_base : public binder_base<ReturnType>
{
public:
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) ();

protected:
    funcptr_type _f;

    binder_function_base (size_t size, funcptr_type f)
        : binder_base<ReturnType>(size)
        , _f(f)
    {}

public:
    virtual ~binder_function_base () {}
};

template <typename Class, typename ReturnType>
class binder_method_base : public binder_base<ReturnType>
{
public:
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) ();

protected:
    Class * _p;
    funcptr_type _f;

    binder_method_base (size_t size, funcptr_type f, Class * p)
        : binder_base<ReturnType>(size)
        , _p(p)
        , _f(f)
    { }

public:
    virtual ~binder_method_base () {}
};

template <typename ReturnType>
class binder_function0 : public binder_function_base<ReturnType>
{

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) ();

    binder_function0 (funcptr_type f)
        : base_class(sizeof(binder_function0)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
    {}

    virtual ~binder_function0 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f();
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function0(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1>
class binder_function1 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1);

    binder_function1 (funcptr_type f, Arg1 a1)
        : base_class(sizeof(binder_function1)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
    {}

    virtual ~binder_function1 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function1(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1, typename Arg2>
class binder_function2 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1, Arg2);

    binder_function2 (funcptr_type f, Arg1 a1, Arg2 a2)
        : base_class(sizeof(binder_function2)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
        , _a2(a2)
    {}

    virtual ~binder_function2 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1, _a2);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function2(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1, typename Arg2, typename Arg3>
class binder_function3 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1, Arg2, Arg3);

    binder_function3 (funcptr_type f, Arg1 a1, Arg2 a2, Arg3 a3)
        : base_class(sizeof(binder_function3)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
    {}

    virtual ~binder_function3 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1, _a2, _a3);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function3(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
class binder_function4 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1, Arg2, Arg3, Arg4);

    binder_function4 (funcptr_type f, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4)
        : base_class(sizeof(binder_function4)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
    {}

    virtual ~binder_function4 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1, _a2, _a3, _a4);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function4(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
class binder_function5 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5);

    binder_function5 (funcptr_type f, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5)
        : base_class(sizeof(binder_function5)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
    {}

    virtual ~binder_function5 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1, _a2, _a3, _a4, _a5);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function5(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
class binder_function6 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;
    typename binder_type_trait<Arg6>::type _a6;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);

    binder_function6 (funcptr_type f, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6)
        : base_class(sizeof(binder_function6)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
        , _a6(a6)
    {}

    virtual ~binder_function6 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1, _a2, _a3, _a4, _a5, _a6);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function6(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
class binder_function7 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;
    typename binder_type_trait<Arg6>::type _a6;
    typename binder_type_trait<Arg7>::type _a7;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);

    binder_function7 (funcptr_type f, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7)
        : base_class(sizeof(binder_function7)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
        , _a6(a6)
        , _a7(a7)
    {}

    virtual ~binder_function7 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function7(*this)) + 1;
//    }
};

template <typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
class binder_function8 : public binder_function_base<ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;
    typename binder_type_trait<Arg6>::type _a6;
    typename binder_type_trait<Arg7>::type _a7;
    typename binder_type_trait<Arg8>::type _a8;

public:
    typedef binder_function_base<ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8);

    binder_function8 (funcptr_type f, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8)
        : base_class(sizeof(binder_function8)
                , reinterpret_cast<typename base_class::funcptr_type>(f))
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
        , _a6(a6)
        , _a7(a7)
        , _a8(a8)
    {}

    virtual ~binder_function8 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return f(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_function8(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType>
class binder_method0 : public binder_method_base<Class, ReturnType>
{

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) ();

    binder_method0 (funcptr_type f, Class * p)
        : base_class(sizeof(binder_method0)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
    {}

    virtual ~binder_method0 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)();
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method0(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1>
class binder_method1 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1);

    binder_method1 (funcptr_type f, Class * p, Arg1 a1)
        : base_class(sizeof(binder_method1)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
    {}

    virtual ~binder_method1 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method1(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1, typename Arg2>
class binder_method2 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1, Arg2);

    binder_method2 (funcptr_type f, Class * p, Arg1 a1, Arg2 a2)
        : base_class(sizeof(binder_method2)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
        , _a2(a2)
    {}

    virtual ~binder_method2 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1, _a2);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method2(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1, typename Arg2, typename Arg3>
class binder_method3 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1, Arg2, Arg3);

    binder_method3 (funcptr_type f, Class * p, Arg1 a1, Arg2 a2, Arg3 a3)
        : base_class(sizeof(binder_method3)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
    {}

    virtual ~binder_method3 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1, _a2, _a3);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method3(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
class binder_method4 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1, Arg2, Arg3, Arg4);

    binder_method4 (funcptr_type f, Class * p, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4)
        : base_class(sizeof(binder_method4)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
    {}

    virtual ~binder_method4 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1, _a2, _a3, _a4);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method4(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
class binder_method5 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5);

    binder_method5 (funcptr_type f, Class * p, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5)
        : base_class(sizeof(binder_method5)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
    {}

    virtual ~binder_method5 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1, _a2, _a3, _a4, _a5);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method5(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
class binder_method6 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;
    typename binder_type_trait<Arg6>::type _a6;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);

    binder_method6 (funcptr_type f, Class * p, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6)
        : base_class(sizeof(binder_method6)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
        , _a6(a6)
    {}

    virtual ~binder_method6 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1, _a2, _a3, _a4, _a5, _a6);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method6(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
class binder_method7 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;
    typename binder_type_trait<Arg6>::type _a6;
    typename binder_type_trait<Arg7>::type _a7;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);

    binder_method7 (funcptr_type f, Class * p, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7)
        : base_class(sizeof(binder_method7)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
        , _a6(a6)
        , _a7(a7)
    {}

    virtual ~binder_method7 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method7(*this)) + 1;
//    }
};

template <typename Class, typename ReturnType, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
class binder_method8 : public binder_method_base<Class, ReturnType>
{
    typename binder_type_trait<Arg1>::type _a1;
    typename binder_type_trait<Arg2>::type _a2;
    typename binder_type_trait<Arg3>::type _a3;
    typename binder_type_trait<Arg4>::type _a4;
    typename binder_type_trait<Arg5>::type _a5;
    typename binder_type_trait<Arg6>::type _a6;
    typename binder_type_trait<Arg7>::type _a7;
    typename binder_type_trait<Arg8>::type _a8;

public:
    typedef binder_method_base<Class, ReturnType> base_class;
    typedef ReturnType return_type;
    typedef return_type (Class::* funcptr_type) (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8);

    binder_method8 (funcptr_type f, Class * p, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8)
        : base_class(sizeof(binder_method8)
                , reinterpret_cast<typename base_class::funcptr_type>(f), p)
        , _a1(a1)
        , _a2(a2)
        , _a3(a3)
        , _a4(a4)
        , _a5(a5)
        , _a6(a6)
        , _a7(a7)
        , _a8(a8)
    {}

    virtual ~binder_method8 () {}

    virtual return_type operator () () const
    {
        funcptr_type f = reinterpret_cast<funcptr_type>(this->_f);
        return (base_class::_p->*f)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
    }

//protected:
//    virtual void * placement_copy (void * ptr) const
//    {
//        return (new (ptr) binder_method8(*this)) + 1;
//    }
};


} // pfs

#endif /* __PFS_BINDER_HPP__ */

