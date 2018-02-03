#include <iostream>
#include <pfs/test/test.hpp>
#include <pfs/json/json.hpp>
#include <pfs/json/rpc.hpp>
#include <pfs/traits/stdcxx/string.hpp>
#include <pfs/traits/stdcxx/vector.hpp>
#include <pfs/traits/stdcxx/map.hpp>

// Enabled by `qt_enable`
#ifdef HAVE_QT_CORE
#   include <pfs/traits/qt/string.hpp>
#   include <pfs/traits/qt/vector.hpp>
#   include <pfs/traits/qt/map.hpp>
#endif

namespace stdcxx {

typedef pfs::string<pfs::stdcxx::string> string_t;
typedef pfs::json::traits<
          bool
        , intmax_t
        , double
        , string_t
        , pfs::stdcxx::vector
        , pfs::stdcxx::map> json_traits;

typedef pfs::json::json<json_traits> json_t;

typedef pfs::json::rpc::traits<json_t
        , string_t
        , int // id type
        , pfs::stdcxx::map> traits_t;

} //stdcxx::json

#ifdef HAVE_QT_CORE

namespace qt {

typedef pfs::string<pfs::qt::string> string_t;
typedef pfs::json::traits<
          bool
        , intmax_t
        , double
        , string_t
        , pfs::qt::vector
        , pfs::qt::map> json_traits;

typedef pfs::json::json<json_traits> json_t;

typedef pfs::json::rpc::traits<json_t
        , string_t
        , int // id type
        , pfs::qt::map> traits_t;
} // qt

#endif


static int counter = 0;

enum {
      RQ_UNKNOWN_METHOD
    , RQ_METHOD1
    , RQ_METHOD2
    , RQ_FAULTY_METHOD
};

template <typename Traits>
void method1 (typename Traits::json_type const & request
        , typename Traits::json_type & response)
{
    std::cout << "method1: "
            << pfs::to_string<typename Traits::string_type>(request)
            << std::endl;

    response = pfs::json::rpc::make_success<Traits>(pfs::json::rpc::id<Traits>(request));
    ++counter;
}

template <typename Traits>
void method2 (typename Traits::json_type const & request
        , typename Traits::json_type & response)
{
    std::cout << "method2: "
            << pfs::to_string<typename Traits::string_type>(request)
            << std::endl;

    response = pfs::json::rpc::make_success<Traits>(pfs::json::rpc::id<Traits>(request));
    ++counter;
}

template <typename Traits>
void faulty_method (typename Traits::json_type const & request
        , typename Traits::json_type & response)
{
    std::cout << "faulty_method: "
            << pfs::to_string<typename Traits::string_type>(request)
            << std::endl;

    response = pfs::json::rpc::make_error<Traits>(pfs::json::rpc::id<Traits>(request)
            , pfs::json::rpc::INVALID_PARAMS);
    ++counter;
}

template <typename Traits>
void notify1 (typename Traits::json_type const & n)
{
    std::cout << "notify1: "
            << pfs::to_string<typename Traits::string_type>(n)
            << std::endl;
    ++counter;
}

template <typename Traits>
void notify2 (typename Traits::json_type const & n)
{
    std::cout << "notify2: "
            << pfs::to_string<typename Traits::string_type>(n)
            << std::endl;
    ++counter;
}

template <typename Traits>
void method1_result_handler (typename Traits::json_type const & result)
{
    std::cout << "method1_result_handler: "
            << pfs::to_string<typename Traits::string_type>(result)
            << std::endl;
    ++counter;
}

template <typename Traits>
void method2_result_handler (typename Traits::json_type const & result)
{
    std::cout << "method2_result_handler: "
            << pfs::to_string<typename Traits::string_type>(result)
            << std::endl;
    ++counter;
}

template <typename Traits>
void default_error_handler (typename Traits::json_type const & error)
{
    std::cout << "default_error_handler: "
            << pfs::to_string<typename Traits::string_type>(error)
            << std::endl;
    ++counter;
}

template <typename Traits>
void method_not_found_error_handler (typename Traits::json_type const & error)
{
    std::cout << "method_not_found_error_handler: "
            << pfs::to_string<typename Traits::string_type>(error)
            << std::endl;
    ++counter;
}

template <typename Traits>
void test ()
{
    ADD_TESTS(1);

    typedef typename Traits::json_type     json_t;
    typedef pfs::json::rpc::server<Traits> server_t;
    typedef pfs::json::rpc::client<Traits> client_t;

    server_t server;
    server.register_method("method1", method1<Traits>);
    server.register_method("method2", method2<Traits>);
    server.register_method("faulty_method", faulty_method<Traits>);
    server.register_notification("notify1", notify1<Traits>);
    server.register_notification("notify2", notify2<Traits>);

    client_t client;
    client.register_result_handler(RQ_METHOD1, method1_result_handler<Traits>);
    client.register_result_handler(RQ_METHOD2, method2_result_handler<Traits>);
    client.register_error_handler(pfs::json::rpc::METHOD_NOT_FOUND, method_not_found_error_handler<Traits>);
    client.set_default_error_handler(default_error_handler<Traits>);

    json_t m1 = pfs::json::rpc::make_request<Traits>(RQ_METHOD1, "method1");
    json_t m2 = pfs::json::rpc::make_request<Traits>(RQ_METHOD2, "method2", json_t(123));
    json_t m3 = pfs::json::rpc::make_request<Traits>(RQ_UNKNOWN_METHOD, "method_unknown");
    json_t m4 = pfs::json::rpc::make_request<Traits>(RQ_FAULTY_METHOD, "faulty_method");
    json_t n1 = pfs::json::rpc::make_notification<Traits>("notify1");
    json_t n2 = pfs::json::rpc::make_notification<Traits>("notify2", json_t(456));

    json_t response;

    server.exec(m1, response);
    client.handle(response);

    server.exec(m2, response);
    client.handle(response);

    server.exec(m3, response);
    client.handle(response);

    server.exec(m4, response);
    client.handle(response);

    server.exec(n1, response);
    client.handle(response);

    server.exec(n2, response);
    client.handle(response);

    TEST_OK2(counter == 9, "All methods/notifications/handlers executed");
}

int main ()
{
    BEGIN_TESTS(0);

    test<stdcxx::traits_t>();

//#ifdef HAVE_QT_CORE
//    test<qt::traits_t>();
//#endif

    return END_TESTS;
}