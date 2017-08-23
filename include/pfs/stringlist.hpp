
/* 
 * File:   stringlist.hpp
 * Author: wladt
 *
 * Created on August 4, 2017, 8:58 AM
 */

#ifndef __PFS_STRINGLIST_HPP__
#define __PFS_STRINGLIST_HPP__

#include <pfs/algo/split.hpp>
#include <pfs/traits/stdcxx/list.hpp>
#include <pfs/traits/sequence_container.hpp>

namespace pfs {

template <typename StringType, template <typename> class ContainerValueRef = traits::stdcxx::list>
class stringlist : public traits::sequence_container<StringType, ContainerValueRef>
{
    typedef traits::sequence_container<StringType, ContainerValueRef> base_class;
    
public:
   	typedef typename base_class::value_type value_type;
	typedef typename base_class::difference_type difference_type;
    typedef StringType string_type;
    
public:
    stringlist () : base_class() {}
    
    void split (string_type const & s, string_type const & separator
            , bool flag = keep_empty)
    {
        pfs::split(s.begin(), s.end(), separator.begin(), separator.end(), flag, this);
    }
};

} // pfs

#endif /* __PFS_STRINGLIST_HPP__ */

