#if __FIXME__

#pragma once
#include <libpq-fe.h>
#include <pfs/exception.hpp>
#include <pfs/traits/db/tags.hpp>
#include <pfs/traits/db/database.hpp>

namespace pfs {
namespace db {

typedef <typename StringT>
struct database_traits<postgresql_tag>
{
    typedef pfs::string string_type;
    typedef db::exception exception;

    typedef struct data
    {
        PGconn * conn;
        string_type errstr; // last error description

        data () : conn(0) {}
    } data_type;

    static bool xopen (data_type & d, string_type const & uri, error_code & ec);
    static void xclose (data_type & d);
};

//
// 31.1.1.2. Connection URIs
//
// The general form for a connection URI is:
//
//    postgresql://[user[:password]@][netloc][:port][/dbname][?param1=value1&...]

// The URI scheme designator can be either postgresql:// or postgres:// .
// Each of the URI parts is optional.The following examples illustrate
// valid URI syntax uses:
//
//    postgresql://
//    postgresql://localhost
//    postgresql://localhost:5433
//    postgresql://localhost/mydb
//    postgresql://user@localhost
//    postgresql://user:secret@localhost
//    postgresql://other@localhost/otherdb?connect_timeout=10&application_name=myapp
//
// Components of the hierarchical part of the URI can also be given
// as parameters. For example:
//
//    postgresql:///mydb?host=localhost&port=5433
//
// Percent-encoding may be used to include symbols with special meaning in any
// of the URI parts.
// Any connection parameters not corresponding to key words listed
// in Section 31.1.2 are ignored and a warning message about them is sent
// to stderr.
// For improved compatibility with JDBC connection URIs, instances of
// parameter ssl=true are translated into sslmode=require.
// The host part may be either host name or an IP address. To specify an IPv6
// host address, enclose it in square brackets:
//
//    postgresql://[2001:db8::1234]/database
//
// The host component is interpreted as described for the parameter host.
// In particular, a Unix-domain socket connection is chosen if the host part is
// either empty or starts with a slash, otherwise a TCP/IP connection is
// initiated. Note, however, that the slash is a reserved character in the
// hierarchical part of the URI. So, to specify a non-standard Unix-domain
// socket directory, either omit the host specification in the URI and specify
// the host as a parameter, or percent-encode the path in the host component of
// the URI:
//
//  postgresql:///dbname?host=/var/lib/postgresql
//  postgresql://%2Fvar%2Flib%2Fpostgresql/dbname
//
bool database_traits<postgresql_tag>::xopen (data_type & d
    , string_type const & uri, error_code & ec)
{
    string_builder sb;

    if (uri.starts_with(string_type("postgresql://"))) {
        sb.push_back("postgresql://");
    }

    sb.push_back(uri);

    // This function will always return a non-null object pointer,
    // unless perhaps there is too little memory even
    // to allocate the PGconn object. The PQstatus function should be called
    // to check the return value for a successful connection before queries
    // are sent via the connection object
    d.conn = PQconnectdb(c_str(sb.str())());

    if (!d.conn) {
        ec = make_error_code(db_errc::bad_alloc);
        return false;
    }

    if (PQstatus(d.conn) != CONNECTION_OK) {
        // Nearly all libpq functions will set a message for PQerrorMessage
        // if they fail. Note that by libpq convention, a nonempty
        // PQerrorMessage result can consist of multiple lines, and will
        // include a trailing newline. The caller should not free the result
        // directly. It will be freed when the associated PGconn handle is
        // passed to PQfinish . The result string should not be expected to
        // remain the same across operations on the PGconn structure.
        d.errstr = PQerrorMessage(d.conn);
        ec = make_error_code(db_errc::open_failed);
        return false;
    }

    return true;
}

void database_traits<postgresql_tag>::xclose (data_type & d)
{
    if (d.conn) {
        // Closes the connection to the server.
        // Also frees memory used by the PGconn object.
        // Note that even if the server connection attempt fails
        // (as indicated by PQstatus ), the application should call PQfinish
        // to free the memory used by the PGconn object.
        // The PGconn pointer must not be used again after
        // PQfinish has been called.
        PQfinish(d.conn);
        d.conn = 0;
    }
}

}} // namespace pfs::db

#endif // __FIXME__