#include <PBD++/details/dynamic_bitset.h>

namespace PBD
{

namespace DynamicBitset
{

std::vector<uint8_t> 
to_uint8_vector(boost::dynamic_bitset<> const& bitset)
{
    std::vector<uint8_t> result;
    for (std::size_t bitset_pos = 0, bitset_end = bitset.size();
         bitset_pos < bitset_end; bitset_pos += 8) {
        uint8_t byte = 0;
        for (std::size_t result_pos = 0; result_pos < 8; ++result_pos) {
            if (bitset_pos + result_pos == bitset.size()) break;
            byte |= bitset[bitset_pos + result_pos] << result_pos;
        }
        result.push_back(byte);
    }
    return result;
}

boost::dynamic_bitset<> 
from_uint8_vector(std::vector<uint8_t> const& array)
{
    boost::dynamic_bitset<> result;
    for (std::vector<uint8_t>::const_iterator byte = array.begin(); 
         byte != array.end(); ++byte) {
        for (std::size_t pos = 0; pos < 8; ++pos) {
            bool bit = (*byte & (0x01 << pos)) != 0;
            result.push_back(bit);
        }
    }
    return result;
}

}

}
