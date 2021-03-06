#pragma once
#include <pfs/io/device.hpp>

namespace pfs {
namespace io {

/**
 * @struct pfs::io::null
 * @brief Null device implementation.
 * @see pfs::io::device.
 */
struct null {};

template <>
struct open_params<null>
{
    open_params () {}
};

/**
 * @fn device open_device<null> (const open_params<null> & op, error_code & ex)
 *
 * @brief Open null device.
 *
 * @param op Open device parameters.
 *      @li open_params<null>()
 *          Open null device.
 * @param ex Reference to store error code.
 *
 * @return Device instance.
 */
template <>
device_ptr open_device<null> (open_params<null> const & op, error_code & ex);

}} // pfs::io
