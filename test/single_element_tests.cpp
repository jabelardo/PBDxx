#include <PBD++/details/streams_operators.h>
#include <PBD++/streams.h>
#include <PBD++/element.h>
#include <PBD++/elements/null.h>
#include <PBD++/elements/string.h>
#include <PBD++/elements/boolean.h>
#include <PBD++/elements/integer.h>
#include <PBD++/elements/real.h>
#include <boost/detail/endian.hpp>

#include <boost/test/unit_test.hpp>

using namespace PBD;

BOOST_AUTO_TEST_CASE(test_string_pbd)
{
    std::string const STRING = "12345"; 
    Element string_1 = Element::create_string(STRING);

    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << string_1;
    out.flush();    
    
    BOOST_CHECK_EQUAL(buffer.size(), 8U);
    
    FilterInStream  in(buffer);
    Element element;
    in >> element;    
    String& string_2 = element.as_string();
    
    BOOST_CHECK_EQUAL(element.type_id(), TypeId::string);           
    BOOST_CHECK_EQUAL(string_2.value(), STRING);
}

BOOST_AUTO_TEST_CASE(test_boolean_pbd)
{
    Element boolean_1 = Element::create_boolean(true);

    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << boolean_1;
    out.flush();
        
    BOOST_CHECK_EQUAL(buffer.size(), 2U);
    
    FilterInStream  in(buffer);
    Element element;
    in >> element;    
    Boolean& boolean_2 = element.as_boolean();
    
    BOOST_CHECK_EQUAL(element.type_id(), TypeId::boolean);    
    BOOST_CHECK_EQUAL(boolean_2.value(), true);    
}

BOOST_AUTO_TEST_CASE(test_null_pbd)
{
    Element null_1 = Element::create_null();
    
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << null_1;
    out.flush();
        
    BOOST_CHECK_EQUAL(buffer.size(), 1U);
    
    FilterInStream  in(buffer);
    Element element;
    in >> element;
    element.as_null();
        
    BOOST_CHECK_EQUAL(element.type_id(), TypeId::null);    
}

template<typename PRIMITIVE, TypeId::TypeId PRIMITIVE_TYPE_ID, std::size_t SIZE>
void 
test_integer_element() 
{
    PRIMITIVE number = std::numeric_limits<PRIMITIVE>::max();
    Element element_1 = Element::create_integer(number);
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_1;
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), SIZE);
    FilterInStream  in(buffer);
    Element element_2;
    in >> element_2;
    BOOST_CHECK_EQUAL(element_2.type_id(), PRIMITIVE_TYPE_ID);
    Integer& element_3 = element_2.as_integer();
    BOOST_CHECK_EQUAL(element_3.value(), number);
}

BOOST_AUTO_TEST_CASE(test_int8_integer_pbd) { test_integer_element<int8_t, TypeId::integer, 2>(); }
BOOST_AUTO_TEST_CASE(test_uint8_integer_pbd) { test_integer_element<uint8_t, TypeId::integer, 2>(); }
BOOST_AUTO_TEST_CASE(test_int16_integer_pbd) { test_integer_element<int16_t, TypeId::integer, 3>(); }
BOOST_AUTO_TEST_CASE(test_uint16_integer_pbd) { test_integer_element<uint16_t, TypeId::integer, 3>(); }
BOOST_AUTO_TEST_CASE(test_int32_integer_pbd) { test_integer_element<int32_t, TypeId::integer, 5>(); }
BOOST_AUTO_TEST_CASE(test_uint32_integer_pbd) { test_integer_element<uint32_t, TypeId::integer, 5>(); }
BOOST_AUTO_TEST_CASE(test_int64_integer_pbd) { test_integer_element<int64_t, TypeId::integer, 9>(); }


template<typename PRIMITIVE, TypeId::TypeId PRIMITIVE_TYPE_ID, std::size_t SIZE>
void 
test_real_element() 
{
    PRIMITIVE number = std::numeric_limits<PRIMITIVE>::max();
    Element element_1 = Element::create_real(number);
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_1;
    out.flush();
    BOOST_CHECK_EQUAL(buffer.size(), SIZE);
    FilterInStream  in(buffer);
    Element element_2;
    in >> element_2;
    BOOST_CHECK_EQUAL(element_2.type_id(), PRIMITIVE_TYPE_ID);
    Real& element_3 = element_2.as_real();
    BOOST_CHECK_EQUAL(element_3.value(), number);
}

BOOST_AUTO_TEST_CASE(test_float_real_pbd) { test_real_element<float, TypeId::real, 5>(); }
BOOST_AUTO_TEST_CASE(test_double_real_pbd) { test_real_element<double, TypeId::real, 9>(); }
