#include <PBD++/details/streams_operators.h>
#include <PBD++/streams.h>
#include <boost/detail/endian.hpp>

#include <boost/test/unit_test.hpp>

using namespace PBD;

BOOST_AUTO_TEST_CASE(test_bool)
{       
    std::vector<char> buffer;	
    FilterOutStream out(buffer);

    out << Writer<bool>(false);
    out.flush();	
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(int8_t));
    out << Writer<bool>(true);
    out.flush();	
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(int8_t) * 2);
    out << Writer<bool>(false);
    out.flush();	
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(int8_t) * 3);
    out << Writer<bool>(false);
    out.flush();	
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(int8_t) * 4);
    out << Writer<bool>(true);
    out.flush();	
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(int8_t) * 5);    
    
    FilterInStream  in(buffer);	
    bool data = true;
	
    in >> Reader<bool>(data);
    BOOST_CHECK_EQUAL(data, false);
    in >> Reader<bool>(data);
    BOOST_CHECK_EQUAL(data, true);
    in >> Reader<bool>(data);
    BOOST_CHECK_EQUAL(data, false);
    in >> Reader<bool>(data);
    BOOST_CHECK_EQUAL(data, false);
    in >> Reader<bool>(data);
    BOOST_CHECK_EQUAL(data, true);
}

template <typename PRIMITIVE>
void 
test_primitive()
{
    typedef Writer<PRIMITIVE> PRIMITIVE_WRITER;
    typedef Reader<PRIMITIVE> PRIMITIVE_READER;
    std::vector<char> buffer;	
    FilterOutStream out(buffer);

    out << PRIMITIVE_WRITER(std::numeric_limits<PRIMITIVE>::min());
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(PRIMITIVE));
    out << PRIMITIVE_WRITER(std::numeric_limits<PRIMITIVE>::max() / 4);
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(PRIMITIVE) * 2);
    out << PRIMITIVE_WRITER(std::numeric_limits<PRIMITIVE>::max() / 3);
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(PRIMITIVE) * 3);
    out << PRIMITIVE_WRITER(std::numeric_limits<PRIMITIVE>::max() / 2);
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(PRIMITIVE) * 4);
    out << PRIMITIVE_WRITER(std::numeric_limits<PRIMITIVE>::max());
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(PRIMITIVE) * 5);

    FilterInStream  in(buffer);	
    PRIMITIVE data;
	    
    in >> PRIMITIVE_READER(data);
    BOOST_CHECK_EQUAL(data, std::numeric_limits<PRIMITIVE>::min());
    in >> PRIMITIVE_READER(data);
    BOOST_CHECK_EQUAL(data, std::numeric_limits<PRIMITIVE>::max() / 4);
    in >> PRIMITIVE_READER(data);
    BOOST_CHECK_EQUAL(data, std::numeric_limits<PRIMITIVE>::max() / 3);
    in >> PRIMITIVE_READER(data);
    BOOST_CHECK_EQUAL(data, std::numeric_limits<PRIMITIVE>::max() / 2);
    in >> PRIMITIVE_READER(data);
    BOOST_CHECK_EQUAL(data, std::numeric_limits<PRIMITIVE>::max());
}

BOOST_AUTO_TEST_CASE(test_uint8) { test_primitive<uint8_t>(); }
BOOST_AUTO_TEST_CASE(test_int8) { test_primitive<int8_t>(); }
BOOST_AUTO_TEST_CASE(test_int16) { test_primitive<int16_t>(); }
BOOST_AUTO_TEST_CASE(test_uint16) { test_primitive<uint16_t>(); }
BOOST_AUTO_TEST_CASE(test_int32) { test_primitive<int32_t>(); }
BOOST_AUTO_TEST_CASE(test_uint32) { test_primitive<uint32_t>(); }
BOOST_AUTO_TEST_CASE(test_int64) { test_primitive<int64_t>(); }
BOOST_AUTO_TEST_CASE(test_float) { test_primitive<float>(); }
BOOST_AUTO_TEST_CASE(test_double) { test_primitive<double>(); }

BOOST_AUTO_TEST_CASE(test_bool_array)
{ 
    std::size_t const array_size = std::numeric_limits<unsigned short>::max();
    bool* out_array = new bool[array_size];
    for (std::size_t i = 0; i < array_size; ++i) {
        out_array[i] = (i % 5) != 0;
    }
    
    std::vector<char> buffer;	
    FilterOutStream out(buffer);

    out << ArrayWriter<bool>(out_array, array_size);
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), array_size * sizeof(uint8_t));

    FilterInStream  in(buffer);	
    bool* in_array = new bool[array_size];
    in >> ArrayReader<bool>(in_array, array_size);
    BOOST_CHECK(std::equal(out_array, out_array + array_size, in_array));

    delete [] out_array;
    delete [] in_array;
}

template <typename PRIMITIVE>
void 
test_primitive_array()
{
    typedef ArrayWriter<PRIMITIVE> PRIMITIVE_ARRAY_WRITER;
    typedef ArrayReader<PRIMITIVE> PRIMITIVE_ARRAY_READER;
	
    std::vector<PRIMITIVE> out_array;
    PRIMITIVE const first = std::numeric_limits<PRIMITIVE>::min();
    PRIMITIVE const last  = std::numeric_limits<PRIMITIVE>::max();
    std::size_t const elements = std::numeric_limits<unsigned short>::max();
    PRIMITIVE delta = (last - first)/elements;
    delta = (delta) ? delta : 1;
    for (PRIMITIVE value = first; true; value = value + delta) {
        out_array.push_back(value);
        if (out_array.size() + 1 == elements)
             out_array.push_back(last); break;
    }
    
    std::vector<char> buffer;	
    FilterOutStream out(buffer);
	
    out << PRIMITIVE_ARRAY_WRITER(&out_array[0], out_array.size());
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), out_array.size() * sizeof(PRIMITIVE));
    
    FilterInStream  in(buffer);	
    std::vector<PRIMITIVE> in_array(out_array.size());
    in >> PRIMITIVE_ARRAY_READER(&in_array[0], in_array.size());
    BOOST_CHECK(std::equal(out_array.begin(), out_array.end(), in_array.begin()));
}

BOOST_AUTO_TEST_CASE(test_uint8_array) { test_primitive_array<uint8_t>(); }
BOOST_AUTO_TEST_CASE(test_int8_array) { test_primitive_array<int8_t>(); }
BOOST_AUTO_TEST_CASE(test_uint16_array) { test_primitive_array<uint16_t>(); }
BOOST_AUTO_TEST_CASE(test_int16_array) { test_primitive_array<int16_t>(); }
BOOST_AUTO_TEST_CASE(test_uint32_array) { test_primitive_array<uint32_t>(); }
BOOST_AUTO_TEST_CASE(test_int32_array) { test_primitive_array<int32_t>(); }
BOOST_AUTO_TEST_CASE(test_int64_array) { test_primitive_array<int64_t>(); }
BOOST_AUTO_TEST_CASE(test_float_array) { test_primitive_array<float>(); }
BOOST_AUTO_TEST_CASE(test_double_array) { test_primitive_array<double>(); }

template<typename PRIMITIVE>
void
test_pbd_vector()
{
    typedef VectorWriter<PRIMITIVE> PRIMITIVE_VECTOR_WRITER;
    typedef VectorReader<PRIMITIVE> PRIMITIVE_VECTOR_READER;
    std::vector<PRIMITIVE> out_array;
    PRIMITIVE const first = std::numeric_limits<PRIMITIVE>::min();
    PRIMITIVE const last  = std::numeric_limits<PRIMITIVE>::max();
    std::size_t const elements = std::numeric_limits<unsigned short>::max();
    PRIMITIVE delta = (last - first)/elements;
    delta = (delta) ? delta : PRIMITIVE(1);
    for (PRIMITIVE value = first; true; value = value + delta) {
        out_array.push_back(value);
        if (out_array.size() + 1 == elements) {
             out_array.push_back(last); 
             break;
         }
    }
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << PRIMITIVE_VECTOR_WRITER(out_array);
    out.flush();
    
    FilterInStream  in(buffer);
    std::vector<PRIMITIVE> in_array;
    in >> PRIMITIVE_VECTOR_READER(in_array);
    
    BOOST_CHECK_EQUAL((buffer.size()), sizeof(uint16_t) + (out_array.size() * sizeof(PRIMITIVE)));
    BOOST_CHECK_EQUAL((buffer.size()), sizeof(uint16_t) + (in_array.size() * sizeof(PRIMITIVE)));    
    BOOST_CHECK_EQUAL(memcmp(&out_array[0], &in_array[0], out_array.size()), 0);
}

BOOST_AUTO_TEST_CASE(test_uint8_pbd_vector) { test_pbd_vector<uint8_t>(); }
BOOST_AUTO_TEST_CASE(test_int8_pbd_vector) { test_pbd_vector<int8_t>(); }
BOOST_AUTO_TEST_CASE(test_uint16_pbd_vector) { test_pbd_vector<uint16_t>(); }
BOOST_AUTO_TEST_CASE(test_int16_pbd_vector) { test_pbd_vector<int16_t>(); }
BOOST_AUTO_TEST_CASE(test_uint32_pbd_vector) { test_pbd_vector<uint32_t>(); }
BOOST_AUTO_TEST_CASE(test_int32_pbd_vector) { test_pbd_vector<int32_t>(); }
BOOST_AUTO_TEST_CASE(test_int64_pbd_vector) { test_pbd_vector<int64_t>(); }
BOOST_AUTO_TEST_CASE(test_float_pbd_vector) { test_pbd_vector<float>(); }
BOOST_AUTO_TEST_CASE(test_double_pbd_vector) { test_pbd_vector<double>(); }

int64_t
get_random()
{
    return 1 + int64_t(
               double(std::numeric_limits<int64_t>::max())
               * double(rand() / (RAND_MAX + 1.0L)));
}

template<typename PRIMITIVE>
void
test_pbd_vector_vacio()
{
    typedef std::vector<PRIMITIVE> VECTOR_TYPE;
    typedef VectorWriter<PRIMITIVE> PRIMITIVE_VECTOR_WRITER;
    typedef VectorReader<PRIMITIVE> PRIMITIVE_VECTOR_READER;
    
    VECTOR_TYPE vector;    
    
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    
    out << PRIMITIVE_VECTOR_WRITER(vector);

    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), vector.size() + sizeof(uint16_t));

    int64_t const random = get_random();
    out << Writer<int64_t>(random);
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), vector.size() + sizeof(uint16_t) + sizeof(int64_t));
            
    FilterInStream  in(buffer);
    
    VECTOR_TYPE vector_in;
    int64_t random_in;
    in >> PRIMITIVE_VECTOR_READER(vector_in);
    BOOST_CHECK(vector_in == vector);
    in >> Reader<int64_t>(random_in);
    
    BOOST_CHECK_EQUAL(random_in, random);
}


BOOST_AUTO_TEST_CASE(test_uint8_pbd_vector_vacio) { test_pbd_vector_vacio<uint8_t>(); }
BOOST_AUTO_TEST_CASE(test_int8_pbd_vector_vacio) { test_pbd_vector_vacio<int8_t>(); }
BOOST_AUTO_TEST_CASE(test_uint16_pbd_vector_vacio) { test_pbd_vector_vacio<uint16_t>(); }
BOOST_AUTO_TEST_CASE(test_int16_pbd_vector_vacio) { test_pbd_vector_vacio<int16_t>(); }
BOOST_AUTO_TEST_CASE(test_uint32_pbd_vector_vacio) { test_pbd_vector_vacio<uint32_t>(); }
BOOST_AUTO_TEST_CASE(test_int32_pbd_vector_vacio) { test_pbd_vector_vacio<int32_t>(); }
BOOST_AUTO_TEST_CASE(test_int64_pbd_vector_vacio) { test_pbd_vector_vacio<int64_t>(); }
BOOST_AUTO_TEST_CASE(test_float_pbd_vector_vacio) { test_pbd_vector_vacio<float>(); }
BOOST_AUTO_TEST_CASE(test_double_pbd_vector_vacio) { test_pbd_vector_vacio<double>(); }
