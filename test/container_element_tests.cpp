#define PBD_UNIT_TEST_
#include <PBD++/element.h>
#include <PBD++/elements.h>
#include <PBD++/exceptions.h>
#include <boost/detail/endian.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>

#include <boost/test/unit_test.hpp>

using namespace PBD;

BOOST_AUTO_TEST_CASE(test_string_array)
{
    Element element_0 = Element::create_string_array();
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");

    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_0;
    out.flush(); 

    FilterInStream  in(buffer);
    Element element_1;
    in >> element_1;
    
    std::vector<std::string> string_vector = element_1.as_string_array().value();
    
    BOOST_CHECK_EQUAL(string_vector.size(), 5U);
    if (!string_vector.empty()) {
        BOOST_CHECK_EQUAL(string_vector[0], "true");
    	BOOST_CHECK_EQUAL(string_vector[1], "true");
    	BOOST_CHECK_EQUAL(string_vector[2], "false");
    	BOOST_CHECK_EQUAL(string_vector[3], "true");
    	BOOST_CHECK_EQUAL(string_vector[4], "false");
    } else {
    	BOOST_CHECK(false);
    }
}

BOOST_AUTO_TEST_CASE(test_boolean_array)
{
    Element element_0 = Element::create_boolean_array();
    element_0.as_boolean_array().push_back(true);
    element_0.as_boolean_array().push_back(true);
    element_0.as_boolean_array().push_back(false);
    element_0.as_boolean_array().push_back(true);
    element_0.as_boolean_array().push_back(false);
	
    boost::dynamic_bitset<> dynamic_bitset_0 = element_0.as_boolean_array().value();        
    BOOST_CHECK_EQUAL(dynamic_bitset_0.size(), 5U);
	
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_0;
    out.flush(); 

    FilterInStream  in(buffer);
    Element element_1;
    in >> element_1;
    
    boost::dynamic_bitset<> dynamic_bitset_1 = element_1.as_boolean_array().value();        
    BOOST_CHECK_EQUAL(dynamic_bitset_1.size(), 5U);
    
    if (!dynamic_bitset_1.empty()) {
        BOOST_CHECK_EQUAL(dynamic_bitset_1[0], true);
        BOOST_CHECK_EQUAL(dynamic_bitset_1[1], true);
        BOOST_CHECK_EQUAL(dynamic_bitset_1[2], false);
        BOOST_CHECK_EQUAL(dynamic_bitset_1[3], true);
        BOOST_CHECK_EQUAL(dynamic_bitset_1[4], false);
    } else {
        BOOST_CHECK(false);
    }
}

BOOST_AUTO_TEST_CASE(test_integer_array)
{	
    int64_t const val_1 = std::numeric_limits<int64_t>::min();
    int64_t const val_2 = std::numeric_limits<int64_t>::max() / 4;
    int64_t const val_3 = std::numeric_limits<int64_t>::max() / 3;
    int64_t const val_4 = std::numeric_limits<int64_t>::max() / 2;
    int64_t const val_5 = std::numeric_limits<int64_t>::max();
           
    Element element_0 = Element::create_integer_array();
    element_0.as_integer_array().push_back(val_1);
    element_0.as_integer_array().push_back(val_2);
    element_0.as_integer_array().push_back(val_3);
    element_0.as_integer_array().push_back(val_4);
    element_0.as_integer_array().push_back(val_5);
	
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_0;
    out.flush(); 
        
    uint16_t const size = 5;
    
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[0], TypeId::int64_array);   

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[1], ((uint8_t const*)(&size))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[2], ((uint8_t const*)(&size))[1]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[3], ((uint8_t const*)(&val_1))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[4], ((uint8_t const*)(&val_1))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[5], ((uint8_t const*)(&val_1))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[6], ((uint8_t const*)(&val_1))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[7], ((uint8_t const*)(&val_1))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[8], ((uint8_t const*)(&val_1))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[9], ((uint8_t const*)(&val_1))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[10], ((uint8_t const*)(&val_1))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[11], ((uint8_t const*)(&val_2))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[12], ((uint8_t const*)(&val_2))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[13], ((uint8_t const*)(&val_2))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[14], ((uint8_t const*)(&val_2))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[15], ((uint8_t const*)(&val_2))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[16], ((uint8_t const*)(&val_2))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[17], ((uint8_t const*)(&val_2))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[18], ((uint8_t const*)(&val_2))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[19], ((uint8_t const*)(&val_3))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[20], ((uint8_t const*)(&val_3))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[21], ((uint8_t const*)(&val_3))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[22], ((uint8_t const*)(&val_3))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[23], ((uint8_t const*)(&val_3))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[24], ((uint8_t const*)(&val_3))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[25], ((uint8_t const*)(&val_3))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[26], ((uint8_t const*)(&val_3))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[27], ((uint8_t const*)(&val_4))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[28], ((uint8_t const*)(&val_4))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[29], ((uint8_t const*)(&val_4))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[30], ((uint8_t const*)(&val_4))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[31], ((uint8_t const*)(&val_4))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[32], ((uint8_t const*)(&val_4))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[33], ((uint8_t const*)(&val_4))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[34], ((uint8_t const*)(&val_4))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[35], ((uint8_t const*)(&val_5))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[36], ((uint8_t const*)(&val_5))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[37], ((uint8_t const*)(&val_5))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[38], ((uint8_t const*)(&val_5))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[39], ((uint8_t const*)(&val_5))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[40], ((uint8_t const*)(&val_5))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[41], ((uint8_t const*)(&val_5))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[42], ((uint8_t const*)(&val_5))[7]);    
    BOOST_CHECK_EQUAL(buffer.size(), 43U);
    
    FilterInStream  in(buffer);
    Element element_1;
    in >> element_1;
    
    std::vector<int64_t> vector = element_1.as_integer_array().value();
    
    BOOST_CHECK_EQUAL(vector.size(), 5U);
    BOOST_CHECK_EQUAL(vector[0], val_1);
    BOOST_CHECK_EQUAL(vector[1], val_2);
    BOOST_CHECK_EQUAL(vector[2], val_3);
    BOOST_CHECK_EQUAL(vector[3], val_4);
    BOOST_CHECK_EQUAL(vector[4], val_5);    
}

BOOST_AUTO_TEST_CASE(test_real_array)
{	
    double const val_1 = std::numeric_limits<double>::min();
    double const val_2 = std::numeric_limits<double>::max() / 4;
    double const val_3 = std::numeric_limits<double>::max() / 3;
    double const val_4 = std::numeric_limits<double>::max() / 2;
    double const val_5 = std::numeric_limits<double>::max();
           
    Element element_0 = Element::create_real_array();
    element_0.as_real_array().push_back(val_1);
    element_0.as_real_array().push_back(val_2);
    element_0.as_real_array().push_back(val_3);
    element_0.as_real_array().push_back(val_4);
    element_0.as_real_array().push_back(val_5);
	
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_0;
    out.flush(); 
        
    uint16_t const size = 5;
    
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[0], TypeId::double_array);   

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[1], ((uint8_t const*)(&size))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[2], ((uint8_t const*)(&size))[1]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[3], ((uint8_t const*)(&val_1))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[4], ((uint8_t const*)(&val_1))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[5], ((uint8_t const*)(&val_1))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[6], ((uint8_t const*)(&val_1))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[7], ((uint8_t const*)(&val_1))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[8], ((uint8_t const*)(&val_1))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[9], ((uint8_t const*)(&val_1))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[10], ((uint8_t const*)(&val_1))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[11], ((uint8_t const*)(&val_2))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[12], ((uint8_t const*)(&val_2))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[13], ((uint8_t const*)(&val_2))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[14], ((uint8_t const*)(&val_2))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[15], ((uint8_t const*)(&val_2))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[16], ((uint8_t const*)(&val_2))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[17], ((uint8_t const*)(&val_2))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[18], ((uint8_t const*)(&val_2))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[19], ((uint8_t const*)(&val_3))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[20], ((uint8_t const*)(&val_3))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[21], ((uint8_t const*)(&val_3))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[22], ((uint8_t const*)(&val_3))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[23], ((uint8_t const*)(&val_3))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[24], ((uint8_t const*)(&val_3))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[25], ((uint8_t const*)(&val_3))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[26], ((uint8_t const*)(&val_3))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[27], ((uint8_t const*)(&val_4))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[28], ((uint8_t const*)(&val_4))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[29], ((uint8_t const*)(&val_4))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[30], ((uint8_t const*)(&val_4))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[31], ((uint8_t const*)(&val_4))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[32], ((uint8_t const*)(&val_4))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[33], ((uint8_t const*)(&val_4))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[34], ((uint8_t const*)(&val_4))[7]);

    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[35], ((uint8_t const*)(&val_5))[0]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[36], ((uint8_t const*)(&val_5))[1]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[37], ((uint8_t const*)(&val_5))[2]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[38], ((uint8_t const*)(&val_5))[3]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[39], ((uint8_t const*)(&val_5))[4]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[40], ((uint8_t const*)(&val_5))[5]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[41], ((uint8_t const*)(&val_5))[6]);
    BOOST_CHECK_EQUAL((uint8_t const)(&buffer[0])[42], ((uint8_t const*)(&val_5))[7]);    
    BOOST_CHECK_EQUAL(buffer.size(), 43U);
    
    FilterInStream  in(buffer);
    Element element_1;
    in >> element_1;
    
    std::vector<double> vector = element_1.as_real_array().value();
    
    BOOST_CHECK_EQUAL(vector.size(), 5U);
    BOOST_CHECK_EQUAL(vector[0], val_1);
    BOOST_CHECK_EQUAL(vector[1], val_2);
    BOOST_CHECK_EQUAL(vector[2], val_3);
    BOOST_CHECK_EQUAL(vector[3], val_4);
    BOOST_CHECK_EQUAL(vector[4], val_5);    
}

BOOST_AUTO_TEST_CASE(test_element_array_1)
{
    Element element_0 = Element::create_string_array();
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");
    
    Element element_1 = element_0.clone();
    Element element_2 = element_0.clone();
    Element element_3 = element_0.clone();
    Element element_4 = element_0.clone();
    Element element_5 = element_0.clone();
 
    Element element_6 = Element::create_element_array();

    element_6.as_element_array().push_back(element_1);
    element_6.as_element_array().push_back(element_2);
    element_6.as_element_array().push_back(element_3);
    element_6.as_element_array().push_back(element_4);
    element_6.as_element_array().push_back(element_5);

    std::vector<Element> element_vector_6 = element_6.as_element_array().value();
    BOOST_CHECK_EQUAL(element_vector_6.size(), 5U);

    for (std::vector<Element>::iterator pos = element_vector_6.begin();
         pos != element_vector_6.end(); ++pos)
    {
        BOOST_CHECK_NO_THROW(pos->as_string_array());
        BOOST_CHECK_EQUAL(pos->type_id(), TypeId::string_array);
    }
    
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_6;
    out.flush();
    FilterInStream  in(buffer);
    Element element_7;
    in >> element_7;
    BOOST_CHECK_EQUAL(element_7.type_id(), TypeId::element_array);
    
    std::vector<Element> element_vector_7 = element_7.as_element_array().value();
    BOOST_CHECK_EQUAL(element_vector_7.size(), 5U);
    
    for (std::vector<Element>::iterator pos = element_vector_7.begin();
         pos != element_vector_7.end(); ++pos)
    {
        BOOST_CHECK_NO_THROW(pos->as_string_array());
        BOOST_CHECK_EQUAL(pos->type_id(), TypeId::string_array);
    }
    
    Element element_8 = element_6.clone();
    
    std::vector<Element> element_vector_8 = element_8.as_element_array().value();
    BOOST_CHECK_EQUAL(element_vector_8.size(), 5U);
    
    for (std::vector<Element>::iterator pos = element_vector_8.begin();
         pos != element_vector_8.end(); ++pos)
    {
        BOOST_CHECK_NO_THROW(pos->as_string_array());
        BOOST_CHECK_EQUAL(pos->type_id(), TypeId::string_array);
    }
}

BOOST_AUTO_TEST_CASE(test_element_array_2)
{
    Element element_0 = Element::create_string_array();
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");
    
    Element element_1 = element_0.clone();
    Element element_2 = element_0.clone();
    Element element_3 = element_0.clone();
    Element element_4 = element_0.clone();
    Element element_5 = element_0.clone();

    Element element_6 = Element::create_element_array();

    element_6.as_element_array().push_back(element_1);
    element_6.as_element_array().push_back(element_2);
    element_6.as_element_array().push_back(element_3);
    element_6.as_element_array().push_back(element_4);
    element_6.as_element_array().push_back(element_5);

    Element element_7 = element_6.clone();
    Element element_8 = element_6.clone();

    Element element_9 = Element::create_element_array();
    element_9.as_element_array().push_back(element_7);
    element_9.as_element_array().push_back(element_8);

    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_9;
    out.flush();
    FilterInStream  in(buffer);
    Element element_10;
    in >> element_10;
    BOOST_CHECK_EQUAL(element_10.type_id(), TypeId::element_array);

    std::vector<Element> element_vector_10 = element_10.as_element_array().value();
    BOOST_CHECK_EQUAL(element_vector_10.size(), 2U);

    for (std::vector<Element>::iterator element_11 = element_vector_10.begin();
         element_11 != element_vector_10.end(); ++element_11)
    {
        BOOST_CHECK_THROW(element_11->as_string_array(), PBD::BadCast);
        BOOST_CHECK_EQUAL(element_11->type_id(), TypeId::element_array);

        std::vector<Element> element_vector_11 = element_11->as_element_array().value();

        for (std::vector<Element>::iterator element_12 = element_vector_11.begin();
             element_12 != element_vector_11.end(); ++element_12)
        {
            BOOST_CHECK_NO_THROW(element_12->as_string_array());
            BOOST_CHECK_EQUAL(element_12->type_id(), TypeId::string_array);
        }

    }
}

BOOST_AUTO_TEST_CASE(test_element_array_3)
{
	typedef boost::weak_ptr<ElementImplementation> weak_ptr;	
	weak_ptr ptr_1;
	weak_ptr ptr_2;
	weak_ptr ptr_3;
	BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_2.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_3.use_count(), 0);
	{
		Element element_1 = Element::create_element_array();

		ptr_1 = element_1.implementation_;
		BOOST_CHECK_EQUAL(ptr_1.use_count(), 1);
		{
			Element element_2 = Element::create_element_array();
			ptr_2 = element_2.implementation_;						
			BOOST_CHECK_EQUAL(ptr_2.use_count(), 1);
						
			element_1.as_element_array().push_back(element_2);
			ptr_3 = element_1.implementation_;			
			BOOST_CHECK_EQUAL(ptr_3.use_count(), 1);
			BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
			BOOST_CHECK_EQUAL(ptr_2.use_count(), 2);			
		}
		BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
		BOOST_CHECK_EQUAL(ptr_2.use_count(), 1);
		BOOST_CHECK_EQUAL(ptr_3.use_count(), 1);
	}
	BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_2.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_3.use_count(), 0);
}

BOOST_AUTO_TEST_CASE(test_element_array_4)
{
	typedef boost::weak_ptr<ElementImplementation> weak_ptr;	
	weak_ptr ptr_1;
	weak_ptr ptr_2;
	weak_ptr ptr_3;
	weak_ptr ptr_4;
	BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_2.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_3.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_4.use_count(), 0);
	{
		Element element_1 = Element::create_element_array();
		ptr_1 = element_1.implementation_;
		BOOST_CHECK_EQUAL(ptr_1.use_count(), 1);
		{
			Element element_2 = Element::create_element_array();
			ptr_2 = element_2.implementation_;
			BOOST_CHECK_EQUAL(ptr_2.use_count(), 1);
						
			element_1.as_element_array().push_back(element_2);
			ptr_3 = element_1.implementation_;
			BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
			BOOST_CHECK_EQUAL(ptr_3.use_count(), 1);
			BOOST_CHECK_EQUAL(ptr_2.use_count(), 2);
			
			element_2.as_element_array().push_back(element_1);
			ptr_4 = element_2.implementation_;
			BOOST_CHECK_EQUAL(ptr_2.use_count(), 1);
			BOOST_CHECK_EQUAL(ptr_4.use_count(), 1);
			BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
			BOOST_CHECK_EQUAL(ptr_3.use_count(), 2);
		}
		BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
		BOOST_CHECK_EQUAL(ptr_2.use_count(), 1);
		BOOST_CHECK_EQUAL(ptr_3.use_count(), 1);
		BOOST_CHECK_EQUAL(ptr_4.use_count(), 0);
	}
	BOOST_CHECK_EQUAL(ptr_1.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_2.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_3.use_count(), 0);
	BOOST_CHECK_EQUAL(ptr_4.use_count(), 0);
}

BOOST_AUTO_TEST_CASE(test_element_map)
{
    Element element_0 = Element::create_string_array();
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");
    element_0.as_string_array().push_back("true");
    element_0.as_string_array().push_back("false");

    Element element_1 = element_0.clone();
    Element element_2 = element_0.clone();
    Element element_3 = element_0.clone();
    Element element_4 = element_0.clone();
    Element element_5 = element_0.clone();

    Element element_6 = Element::create_element_array();

    element_6.as_element_array().push_back(element_1);
    element_6.as_element_array().push_back(element_2);
    element_6.as_element_array().push_back(element_3);
    element_6.as_element_array().push_back(element_4);
    element_6.as_element_array().push_back(element_5);
    
    Element element_7 = element_6.clone();
    Element element_8 = element_6.clone();
    Element element_9 = element_6.clone();
    Element element_10 = element_6.clone();
    Element element_11 = element_6.clone();

    Element element_12 = Element::create_element_map();
    
    element_12.as_element_map().insert("element_7", element_7);
    element_12.as_element_map().insert("element_8", element_8);
    element_12.as_element_map().insert("element_9", element_9);
    element_12.as_element_map().insert("element_10", element_10);
    element_12.as_element_map().insert("element_11", element_11);
    
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << element_12;
    out.flush();
    FilterInStream  in(buffer);
    Element element_13;
    in >> element_13;

    BOOST_CHECK_EQUAL(element_13.type_id(), TypeId::element_map);
    ElementMap::Data map_13 = element_13.as_element_map().value();
    BOOST_CHECK_EQUAL(map_13.size(), 5U);
    		
    for (ElementMap::Data::iterator pos_map_13 = map_13.begin(); 
    	 pos_map_13 != map_13.end(); ++pos_map_13 ) {

    	BOOST_CHECK_EQUAL(pos_map_13->second.type_id(), TypeId::element_array);
    	
    	std::vector<Element> vector_13 = pos_map_13->second.as_element_array().value();
    	
        for (std::vector<Element>::const_iterator pos_vector_13 = vector_13.begin();
             pos_vector_13 != vector_13.end(); ++pos_vector_13) {
            BOOST_CHECK_NO_THROW(pos_vector_13->as_string_array());
            BOOST_CHECK_EQUAL(pos_vector_13->type_id(), TypeId::string_array);
        }
    }
}
