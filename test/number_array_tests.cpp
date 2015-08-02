#include <PBD++/elements/real_array.h>
#include <PBD++/elements/integer_array.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <boost/detail/endian.hpp>

#include <boost/test/unit_test.hpp>

using namespace PBD;

BOOST_AUTO_TEST_CASE(test_number_array_real)
{
	RealArray::VectorType vect;
	double min_float = std::numeric_limits<float>::min();
	double max_float = std::numeric_limits<float>::max();
	vect.push_back (min_float);
	vect.push_back (max_float);
	RealArray real_array_1 (vect);

	BOOST_CHECK_EQUAL(real_array_1.type_id(), TypeId::real_array);
	BOOST_CHECK_EQUAL(real_array_1.type_id_to_write(), TypeId::float_array);
	BOOST_CHECK_EQUAL(max_float, real_array_1[real_array_1.size() - 1]);

	double max_double = std::numeric_limits<double>::max();
	real_array_1.push_back(max_double);

	BOOST_CHECK_EQUAL(real_array_1.type_id_to_write(), TypeId::double_array);
	BOOST_CHECK_EQUAL(max_double, real_array_1[real_array_1.size() - 1]);

	vect.push_back (max_double);
	RealArray real_array_2 (vect);

	BOOST_CHECK_EQUAL(real_array_2.type_id(), TypeId::real_array);
	BOOST_CHECK_EQUAL(real_array_2.type_id_to_write(), TypeId::double_array);
	BOOST_CHECK_EQUAL(max_double, real_array_2[real_array_2.size() - 1]);
	
	double nan_double = std::numeric_limits<double>::quiet_NaN();

	BOOST_CHECK_THROW(real_array_2.push_back(nan_double), std::invalid_argument);

	BOOST_CHECK_EQUAL(real_array_2.type_id_to_write(), TypeId::double_array);

	double nan_float = std::numeric_limits<float>::quiet_NaN();
	vect.push_back (nan_float);

	BOOST_CHECK_THROW(RealArray real_array_3 (vect), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_number_array_integer_1)
{
    IntegerArray::VectorType vect;
    int64_t min_uint8 = 0;
    int64_t max_uint8 = std::numeric_limits<uint8_t>::max();
	vect.push_back (min_uint8);
	vect.push_back (max_uint8);
    IntegerArray integer_array_1 (vect);

	BOOST_CHECK_EQUAL(integer_array_1.type_id(), TypeId::integer_array);
	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::uint8_array);
	BOOST_CHECK_EQUAL(max_uint8, integer_array_1[integer_array_1.size() - 1]);

	int64_t max_uint16 = std::numeric_limits<uint16_t>::max();
	integer_array_1.push_back(max_uint16);

	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::uint16_array);
	BOOST_CHECK_EQUAL(max_uint16, integer_array_1[integer_array_1.size() - 1]);

	int64_t max_uint32 = std::numeric_limits<uint32_t>::max();
	integer_array_1.push_back(max_uint32);

	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::uint32_array);
	BOOST_CHECK_EQUAL(max_uint32, integer_array_1[integer_array_1.size() - 1]);

	int64_t max_uint64 = std::numeric_limits<uint64_t>::max();
	integer_array_1.push_back(max_uint64);

	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::int64_array);
	BOOST_CHECK_EQUAL(max_uint64, integer_array_1[integer_array_1.size() - 1]);
}

BOOST_AUTO_TEST_CASE(test_number_array_integer_2)
{
    IntegerArray::VectorType vect;
    int64_t min_int8 = std::numeric_limits<int8_t>::min();
    int64_t max_int8 = std::numeric_limits<int8_t>::max();
	vect.push_back (min_int8);
	vect.push_back (max_int8);
    IntegerArray integer_array_1 (vect);

	BOOST_CHECK_EQUAL(integer_array_1.type_id(), TypeId::integer_array);
	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::int8_array);
	BOOST_CHECK_EQUAL(max_int8, integer_array_1[integer_array_1.size() - 1]);

	int64_t max_int16 = std::numeric_limits<int16_t>::max();
	integer_array_1.push_back(max_int16);

	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::int16_array);
	BOOST_CHECK_EQUAL(max_int16, integer_array_1[integer_array_1.size() - 1]);

	int64_t max_int32 = std::numeric_limits<int32_t>::max();
	integer_array_1.push_back(max_int32);

	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::int32_array);
	BOOST_CHECK_EQUAL(max_int32, integer_array_1[integer_array_1.size() - 1]);

	int64_t max_int64 = std::numeric_limits<int64_t>::max();
	integer_array_1.push_back(max_int64);

	BOOST_CHECK_EQUAL(integer_array_1.type_id_to_write(), TypeId::int64_array);
	BOOST_CHECK_EQUAL(max_int64, integer_array_1[integer_array_1.size() - 1]);
}

BOOST_AUTO_TEST_CASE(test_number_array_real_copyTo)
{
    RealArray real_array;
    double min = std::numeric_limits<double>::min();
    double max = std::numeric_limits<double>::max();
    real_array.push_back(min);
    real_array.push_back(max/4);
    real_array.push_back(max/3);
    real_array.push_back(max/2);
    real_array.push_back(max);

    std::vector<double> vector_data(real_array.value());

    BOOST_CHECK_EQUAL(vector_data.size(), 5U);
    BOOST_CHECK_CLOSE(vector_data[0], double(min), double(0.01)); 
    BOOST_CHECK_EQUAL(vector_data[1], double(max/4));
    BOOST_CHECK_EQUAL(vector_data[2], double(max/3));
    BOOST_CHECK_EQUAL(vector_data[3], double(max/2));
    BOOST_CHECK_EQUAL(vector_data[4], double(max));
}

BOOST_AUTO_TEST_CASE(test_number_array_integer_copyTo)
{
    IntegerArray integer_array;
    int64_t min = std::numeric_limits<int64_t>::min();
    int64_t max = std::numeric_limits<int64_t>::max();
    integer_array.push_back(min);
    integer_array.push_back(max/4);
    integer_array.push_back(max/3);
    integer_array.push_back(max/2);
    integer_array.push_back(max);

    std::vector<int64_t> vector_data(integer_array.value());

    BOOST_CHECK_EQUAL(vector_data.size(), 5U);
    BOOST_CHECK_EQUAL(vector_data[0], min);
    BOOST_CHECK_EQUAL(vector_data[1], max/4);
    BOOST_CHECK_EQUAL(vector_data[2], max/3);
    BOOST_CHECK_EQUAL(vector_data[3], max/2);
    BOOST_CHECK_EQUAL(vector_data[4], max);
}

BOOST_AUTO_TEST_CASE(test_number_array_integer_write_read)
{
    IntegerArray integer_array;
    int64_t min = std::numeric_limits<int64_t>::min();
    int64_t max = std::numeric_limits<int64_t>::max();
    integer_array.push_back(min);
    integer_array.push_back(max/4);
    integer_array.push_back(max/3);
    integer_array.push_back(max/2);
    integer_array.push_back(max);

    std::ostringstream out;
    integer_array.write(out, TypeId::int64_array);
    BOOST_CHECK_EQUAL(out.str().size(), sizeof(uint16_t) + sizeof(int64_t) * 5);

    std::istringstream in(out.str());
    IntegerArray integer_array_2;
    integer_array_2.read(in, TypeId::int64_array);

    std::vector<int64_t> vector_data(integer_array_2.value());

    BOOST_CHECK_EQUAL(vector_data.size(), 5U);
    BOOST_CHECK_EQUAL(vector_data[0], min);
    BOOST_CHECK_EQUAL(vector_data[1], max/4);
    BOOST_CHECK_EQUAL(vector_data[2], max/3);
    BOOST_CHECK_EQUAL(vector_data[3], max/2);
    BOOST_CHECK_EQUAL(vector_data[4], max);
}
