#include <PBD++/details/dynamic_bitset.h>
#include <PBD++/streams.h>
#include <PBD++/details/streams_operators.h>
#include <boost/detail/endian.hpp>

#include <boost/test/unit_test.hpp>

using namespace PBD;

BOOST_AUTO_TEST_CASE(test_dynamic_bitset_1)
{
    std::vector<uint8_t> out_array;
    std::size_t const array_size = std::numeric_limits<unsigned short>::max();
    for (std::size_t i = 0; i < array_size; ++i) {
        out_array.push_back((i % 5) != 0) ;
    }

    boost::dynamic_bitset<> in_bitset = DynamicBitset::from_uint8_vector(out_array);
    std::vector<uint8_t> in_array = DynamicBitset::to_uint8_vector(in_bitset);

    BOOST_CHECK(std::equal(out_array.begin(), out_array.end(), in_array.begin()));
}

BOOST_AUTO_TEST_CASE(test_dynamic_bitset_2)
{
    boost::dynamic_bitset<> out_bitset;
    std::size_t const array_size = std::numeric_limits<unsigned short>::max();
    for (std::size_t i = 0; i < array_size; ++i) {
        out_bitset.push_back((i % 5) != 0) ;
    }

    std::vector<uint8_t> in_array = DynamicBitset::to_uint8_vector(out_bitset);
    boost::dynamic_bitset<> in_bitset = DynamicBitset::from_uint8_vector(in_array);
    for (std::size_t i = 0; i < array_size; ++i) {
        BOOST_CHECK(static_cast<bool>(out_bitset[i]) == static_cast<bool>(in_bitset[i]));
    }
}


BOOST_AUTO_TEST_CASE(test_dynamic_bitset_3)
{
    boost::dynamic_bitset<> out_bitset;
    std::size_t const array_size = std::numeric_limits<unsigned short>::max();
    for (std::size_t i = 0; i < array_size; ++i) {
        out_bitset.push_back((i % 5) != 0) ;
    }

    std::vector<uint8_t> out_array = DynamicBitset::to_uint8_vector(out_bitset);

    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << ArrayWriter<uint8_t>(&out_array[0], out_array.size());
    out.flush(); 

    std::size_t const result_size = (out_bitset.size() / 8) + (out_bitset.size() % 8 != 0);

    BOOST_CHECK(buffer.size() == result_size * sizeof(uint8_t));

    FilterInStream  in(buffer);
    std::vector<uint8_t> in_array(out_array.size());
    in >> ArrayReader<uint8_t>(&in_array[0], in_array.size());

    boost::dynamic_bitset<> in_bitset = DynamicBitset::from_uint8_vector(in_array);

    BOOST_CHECK(std::equal(out_array.begin(), out_array.end(), in_array.begin()));
    for (std::size_t i = 0; i < array_size; ++i) {
        BOOST_CHECK(static_cast<bool>(out_bitset[i]) == static_cast<bool>(in_bitset[i]));
    }
}
