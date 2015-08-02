#ifndef PBD_ENDIANESS_H_
#define PBD_ENDIANESS_H_

#include <boost/detail/endian.hpp>

#ifdef BOOST_LITTLE_ENDIAN
#define PBD_LITTLE_ENDIAN 1
#undef PBD_BIG_ENDIAN
#else
#undef PBD_LITTLE_ENDIAN
#define PBD_BIG_ENDIAN 1
#endif

namespace PBD
{
namespace Endianess
{

enum Endianess
{
      big_endian    = 0
    , little_endian = 1
#ifdef BOOST_LITTLE_ENDIAN    
    , arch_endian = little_endian
#else
    , arch_endian = big_endian
#endif    
};

}
}

#endif /*PBD_ENDIANESS_H_*/
