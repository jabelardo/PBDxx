#ifndef PBDXX_DYNAMIC_BITSET_H_
#define PBDXX_DYNAMIC_BITSET_H_

#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <PBD++/details/cstdint.h>

namespace PBD
{

namespace DynamicBitset
{

/**
* Obtiene un un vector de bytes (vector<uint8_t>) a
* partir de conjunto dinamico de bit (boost::dynamic_bitset<>).
* @param bitset conjunto dinamico de bit (boost::dynamic_bitset<>).
* @return un vector de bytes de tipo vector<uint8_t>.
*/
std::vector<uint8_t>
to_uint8_vector(boost::dynamic_bitset<> const& bitset);


/**
* Obtiene un conjunto dinamico de bit (boost::dynamic_bitset<>) a
* partir de un vector de bytes (vector<uint8_t>).
* @param Array un vector de bytes de tipo vector<uint8_t>.
* @return conjunto dinamico de bit (boost::dynamic_bitset<>) .
*/
boost::dynamic_bitset<>
from_uint8_vector(std::vector<uint8_t> const& array);

}

}

#endif /*PBDXX_DYNAMIC_BITSET_H_*/
