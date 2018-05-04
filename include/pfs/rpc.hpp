#pragma once
#include <string>
#include <pfs/endian.hpp>
#include <pfs/memory.hpp>
#include <pfs/types.hpp>
// #include <pfs/byte_string_ostream.hpp>
// #include <pfs/byte_string_istream.hpp>
#include <pfs/byte_string.hpp>
#include <pfs/string.hpp>
#include <pfs/list.hpp>
#include <pfs/map.hpp>
#include <pfs/system_error.hpp>


namespace pfs {

///////////////////////////////////////////////////////////////////////////
// RPC error                                                             //
///////////////////////////////////////////////////////////////////////////

//
//
//     static error_code_type const SERVER_ERROR () { return -32000; }

#if __cplusplus >= 201103L
enum class rpc_errc
{
#else
struct rpc_errc
{
    enum value_enum {
#endif
            no_error = 0              //!< No error.
          , bad_version = 1           //!< Version does not match.
          , id_not_match = 2          //!< Response ID does not match requested.
          , parse_error = -32700      //!< An error occurred on the server while parsing.
          , invalid_request = -32600  //!< Is not a valid request.
          , method_not_found = -32601 //!< The method does not exist / is not available.
          , invalid_params = -32602   //!< Invalid method parameter(s).
          , internal_error = -32603   //!< Intrenal error.
          , invalid_response = -32604 //!< Is not a valid response.
          //
          // -32000 to -32099 Reserved for implementation-defined server-errors.
          //
#if __cplusplus < 201103L
    };

    value_enum v;

    rpc_errc (value_enum x)
        : v(x)
    {}

    rpc_errc & operator = (value_enum x)
    {
        v = x;
        return *this;
    }

    operator int () const
    {
        return static_cast<int>(v);
    }
#endif
};

namespace details {
class rpc_error_category : public pfs::error_category
{
public:
    virtual char const * name () const pfs_noexcept pfs_override;
    virtual std::string message (int ev) const pfs_override;
};
} // details

pfs::error_category const & rpc_error_category ();

inline pfs::error_code make_error_code (rpc_errc e)
{
    return pfs::error_code(static_cast<int>(e), rpc_error_category());
}

class rpc_exception : public logic_error
{
public:
    rpc_exception (pfs::error_code ec)
        : logic_error(rpc_error_category().message(ec.value()))
    {}

    rpc_exception (pfs::error_code ec, char const * what)
        : logic_error(rpc_error_category().message(ec.value())
            + ": " + what)
    {}

    rpc_exception (pfs::error_code ec, std::string const & what)
        : logic_error(rpc_error_category().message(ec.value())
            + ": " + what)
    {}

    virtual ~rpc_exception() throw() {}
};

} // pfs


namespace std {

// TODO implement for C++98
#if __cplusplus >= 201103L

template<>
struct is_error_code_enum<pfs::rpc_errc>
        : public std::true_type
{};

#endif
} // std

namespace pfs {

enum rpc_entity {
      RPC_METHOD       = 1
    , RPC_NOTIFICATION = 2
    , RPC_SUCCESS      = 3
    , RPC_ERROR        = 4
};

///////////////////////////////////////////////////////////////////////////
// ID Generator                                                          //
///////////////////////////////////////////////////////////////////////////

template <typename Id>
struct id_generator
{
    typedef Id type;
    type next_id () const;
};

///////////////////////////////////////////////////////////////////////////
// Serializer                                                            //
///////////////////////////////////////////////////////////////////////////
//
// struct serializer
// {
//      serializer & version (uint8_t major, uint8_t minor);
//      serializer & entity (rpc_entity ent);
//      serializer & method (string_type const & name);
// };
//
///////////////////////////////////////////////////////////////////////////
// Protocol                                                              //
///////////////////////////////////////////////////////////////////////////
//
// struct protocol
// {
// };

///////////////////////////////////////////////////////////////////////////
// Transport                                                             //
///////////////////////////////////////////////////////////////////////////
//
// template <typename Protocol>
// struct transport
// {
//     ssize_t send (pfs::byte_string const &, pfs::error_code & ec);
// //    ssize_t recv (pfs::byte_string &, pfs::error_code & ec);
// };
//

template <uint8_t MajorVersion, uint8_t MinorVersion
        , typename IdGenerator
        , typename Serializer
        , typename Protocol
        , typename StringT = pfs::string
        , template <typename, typename> class AssociativeContainer = pfs::map
        , template <typename> class SequenceContainer = pfs::list>
struct rpc
{
    typedef StringT                     string_type;
    typedef IdGenerator                 id_generator;
    typedef typename id_generator::type id_type;
    typedef Serializer                  serializer_type;
    typedef Protocol                    protocol_type;

    ///////////////////////////////////////////////////////////////////////////
    // Client                                                                //
    ///////////////////////////////////////////////////////////////////////////

    template <template <typename> class Transport>
    class client
    {
        friend struct session;
        typedef Transport<Protocol> transport_type;

        struct session
        {
            id_type         _id;
            client &        _owner;
            serializer_type _serializer;

            session (id_type const & id, client & owner)
                : _id(id)
                , _owner(owner)
            {}

            session & call (string_type const & name)
            {
                _serializer.set_version(MajorVersion, MinorVersion)
                    .set_entity(RPC_METHOD)
                    .set_id(_id)
                    .set_method(name);
                return *this;
            }

            template <typename T>
            inline session & operator () (T const & value)
            {
                _serializer.add_param(value);
                return *this;
            }

            template <typename T>
            inline session & operator () (string_type const & name, T const & value)
            {
                _serializer.add_param(name, value);
                return *this;
            }

#if __cplusplus >= 201103L
            template <typename T, typename ...Args>
            inline session & operator () (T const & value, Args const &... args)
            {
                _serializer.add_param(value);
                return operator () (args...);
            }
#endif

            template <typename T>
            inline T result ()
            {
                T value;
                error_code ec = this->result(value);
                if (ec)
                    throw rpc_exception(ec);
                return value;
            }

            template <typename T>
            error_code result (T & value)
            {
                error_code ec;

                //
                // Send data
                //
                ssize_t n = _owner._transport.send(_serializer.pack(), ec);

                if (n < 0 || ec)
                    return ec;

                //
                // Receive data
                //

                byte_string buffer;
                n = _owner._transport.recv(buffer, ec);

                if (n < 0 || ec)
                    return ec;

                if (! _serializer.unpack(buffer, ec))
                    return ec;

                uint8_t major, minor;
                int entity;
                id_type id;

                if (!_serializer.get_version(major, minor))
                    return make_error_code(rpc_errc::parse_error);

                if (major != MajorVersion || minor != MinorVersion)
                    return make_error_code(rpc_errc::bad_version);

                if (!_serializer.get_entity(entity))
                    return make_error_code(rpc_errc::parse_error);

                if (entity != RPC_SUCCESS)
                    return make_error_code(rpc_errc::invalid_response);

                if (!_serializer.get_id(id))
                    return make_error_code(rpc_errc::parse_error);

                if (id != _id)
                    return make_error_code(rpc_errc::id_not_match);

                if (_serializer.get_value(value))
                    return make_error_code(rpc_errc::parse_error);

                return error_code();
            }
        }; // session

    public:
        client (transport_type & transport)
            : _transport(transport)
        {}

        session & call (string const & method_name)
        {
            id_type id = _id_generator.next_id();
            std::pair<typename session_registry::iterator,bool> r
                    = _sessions.insert(id, session(id, *this));
            PFS_ASSERT(r.second);

            session & sess = session_registry::mapped_reference(r.first);
            return sess.call(method_name);
        }

//         client & notify (string const & method_name)
//         {
//             _protocol.begin_tx();
//             _protocol << RPC_NOTIFICATION();// << id;
//             _protocol << method_name;
//             return *this;
//         }
//
//         // for notify
//         bool send ()
//         {
//             _ec.clear();
//             _protocol.commit_tx();
//             ssize_t n = _transport.send(_protocol.data(), _ec);
//
//             if (n > 0 && !_ec)
//                 return false;
//             return true;
//         }

    private:
        typedef AssociativeContainer<id_type, session> session_registry;

        id_generator     _id_generator;
        transport_type & _transport;
        session_registry _sessions;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Server                                                                //
    ///////////////////////////////////////////////////////////////////////////

    template <template <typename> class Transport>
    class server
    {
        friend struct session;
        typedef Transport<Protocol> transport_type;

        error_code parse ()
        {
            error_code ec;

            //
            // Receive data
            //

            byte_string buffer;
            ssize_t n = _transport.recv(buffer, ec);

            if (n < 0 || ec)
                return ec;

            if (! _serializer.unpack(buffer, ec))
                return ec;

            uint8_t major, minor;
            int entity;
            id_type id;

            if (!_serializer.get_version(major, minor))
                return make_error_code(rpc_errc::parse_error);

            if (major != MajorVersion || minor != MinorVersion)
                return make_error_code(rpc_errc::bad_version);

            if (!_serializer.get_entity(entity))
                return make_error_code(rpc_errc::parse_error);

            if (entity == RPC_METHOD) {
                if (!_serializer.get_id(id))
                    return make_error_code(rpc_errc::parse_error);
                // TODO Handle method
            } else if (entity == RPC_NOTIFICATION) {
                // TODO Handle notification
            } else {
                return make_error_code(rpc_errc::invalid_request);
            }

//                 //
//                 // Send data
//                 //
//                 ssize_t n = _owner._transport.send(_serializer.pack(), ec);
//
//                 if (n < 0 || ec)
//                     return ec;
//
//                 if (_serializer.get_value(value))
//                     return make_error_code(rpc_errc::parse_error);

            return error_code();
        }

        template <typename R>
        struct binder
        {
            virtual error_code operator () (R & result, serializer_type & serializer) = 0;
        };

        template <typename R, typename F>
        struct binder0 : binder<R>
        {
            F _f;
            binder0 (F f) : _f(f) {}

            virtual error_code operator () (R & result, serializer_type & serializer) pfs_override
            {
                if (serializer.has_params())
                    return make_error_code(rpc_errc::invalid_params);

                result = _f();
                return error_code();
            }
        };

        template <typename R, typename F
                , typename A1>
        struct binder1 : binder<R>
        {
            F _f;
            binder1 (F f) : _f(f) {}

            virtual error_code operator () (R & result, serializer_type & serializer) pfs_override
            {
                A1 a1;

                if (!serializer.get_param(a1))
                    return make_error_code(rpc_errc::invalid_params);

                result = _f(a1);
                return error_code();
            }
        };

        template <typename R, typename F
                , typename A1
                , typename A2>
        struct binder2 : binder<R>
        {
            F _f;
            binder2 (F f) : _f(f) {}

            virtual error_code operator () (R & result, serializer_type & serializer) pfs_override
            {
                A1 a1;
                A2 a2;

                if (!serializer.get_param(a1)
                        || !serializer.get_param(a2))
                    return make_error_code(rpc_errc::invalid_params);

                result = _f(a1, a2);
                return error_code();
            }
        };

        template <typename R, typename F
                , typename A1
                , typename A2
                , typename A3>
        struct binder3 : binder<R>
        {
            F _f;
            binder3 (F f) : _f(f) {}

            virtual error_code operator () (R & result, serializer_type & serializer) pfs_override
            {
                A1 a1;
                A2 a2;
                A2 a3;

                if (!serializer.get_param(a1)
                        || !serializer.get_param(a2)
                        || !serializer.get_param(a3))
                    return make_error_code(rpc_errc::invalid_params);

                result = _f(a1, a2, a3);
                return error_code();
            }
        };

        //
        // TODO call_binder4, call_binder5, call_binder6, call_binder7, call_binder8
        //

    public:
        server (transport_type & transport)
            : _transport(transport)
        {}

        template <typename R, typename F>
        void bind (string_type const & name, F f)
        {
            //_repo.insert(name, new binder0<R, F>(f));
        }

        template <typename R, typename F
                , typename A1>
        void bind (string_type const & name, F f)
        {
            //_repo.insert(name, new binder0<R, F, A1>(f));
        }

        template <typename R, typename F
                , typename A1
                , typename A2>
        void bind (string_type const & name, F f)
        {
            //_repo.insert(name, new binder0<R, F, A1, A2>(f));
        }

        template <typename R, typename F
                , typename A1
                , typename A2
                , typename A3>
        void bind (string_type const & name, F f)
        {
            //_repo.insert(name, new binder0<R, F, A1, A2, A3>(f));
        }

        //
        // TODO bind
        //

    private:
        //typedef AssociativeContainer<string_type, binder *> repository_type;

        transport_type & _transport;
        serializer_type  _serializer;
        //repository_type  _repo;
    };

public:

//     //template <typename Protocol, typename Transport>
//     class server
//     {
//     public:
//       //  typedef Transport transport_type;
//
//     private:
// //         struct basic_binder
// //         {
// //             virtual bool call (session &) = 0;
// //         };
//
//         typedef typename rpc::string_type string_type;
//         typedef typename rpc::id_type     id_type;
// //        typedef AssociativeContainer<string_type, pfs::shared_ptr<basic_binder> > repository;
//
//
// //         template <typename F>
// //         struct binder : basic_binder
// //         {
// //             F _f;
// //             function_binder (F f) : _f(f) {}
// //
// //             virtual bool call (session & sess) pfs_override
// //             {
// //
// //             }
//
//     // //         virtual shared_response call (byte_istream & params) pfs_override
//     // //         {
//     // //             return (*_f)(params);
//     // //         }
//     //
//     //         virtual shared_archive call (id_type id, byte_istream & params) pfs_override
//     //         {
//     //             return (*_f)(id, params);
//     //         }
// //        };
//
//
//     public:
//         server () {}
//
//         void exec () {}
//
// //         template <typename F>
// //         inline void bind (string_type const & method_name, F f)
// //         {
// //               typename _repo(method_name
// //                       , pfs::static_pointer_cast<basic_binder>(pfs::make_shared<binder<F>, F>(f)));
// //         }
//
// //          template <typename F, typename A1>
// //          inline void bind (string_type const & method_name, F f, C & c)
// //          {
// // //             typename repository_traits::inserter(_method_repo).insert(method_name
// // //                     , pfs::static_pointer_cast<basic_binder>(pfs::make_shared<method_binder<F, C>, F, C>(f, c)));
// //          }
// #if __COMMENT__
// //         shared_response exec (request & rq)
// //         {
// //             typename repository_traits::finder finder(_method_repo);
// //             typename repository_traits::iterators iterators(_method_repo);
// //
// //             uint8_t major_version;
// //             uint8_t minor_version;
// //             uint8_t rpc_type;
// //             id_type id;
// //             method_name_type method_name;
// //
// //             rq >> major_version >> minor_version >> rpc_type;
// //
// //             if (!(major_version == MAJOR_VERSION && minor_version == MINOR_VERSION))
// //                 return make_error(BAD_VERSION);
// //
// //             if (rpc_type == RPC_METHOD)
// //                 rq >> id;
// //             else if (rpc_type == RPC_NOTIFICATION) {
// //                 ;
// //             } else {
// //                 return make_error();
// //             }
// //
// //             rq >> method_name;
// //
// //             typename repository_traits::const_iterator it = finder.find(method_name);
// //
// //             if (it == iterators.cend()) {
// //                 if (rpc_type == RPC_METHOD)
// //                     return make_error(id, METHOD_NOT_FOUND);
// //                 return make_error(METHOD_NOT_FOUND);
// //             }
// //
// //             shared_binder const & m = iterators.value(it);
// //             return m->call(rq);
// //         }
// #endif
//
//     private:
//         //repository _repo;
// //         protocol_type  _protocol;
// //         transport_type _transport;
//         //typename repository_traits::type _method_repo;
//     };
//
};

} // pfs

