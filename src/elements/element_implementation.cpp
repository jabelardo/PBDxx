#include <PBD++/elements/element_implementation.h>
#include <PBD++/exceptions/bad_cast.h>
#include <PBD++/details/streams_operators.h>

namespace PBD
{

void 
ElementImplementation::destroy(ElementImplementation* e)
{
    delete e;
}

ElementImplementation::ElementImplementation()
{
}

ElementImplementation::~ElementImplementation()
{
}

ElementMap&
ElementImplementation::as_element_map() 
{ 
    throw BadCast("Element is not an ElementMap"); 
}

ElementMap const&
ElementImplementation::as_element_map() const 
{ 
    throw BadCast("Element is not an ElementMap"); 
}

ElementArray&
ElementImplementation::as_element_array() 
{ 
    throw BadCast("Element is not an ElementArray"); 
}

ElementArray const&
ElementImplementation::as_element_array() const 
{ 
    throw BadCast("Element is not an ElementArray"); 
}

StringArray& 
ElementImplementation::as_string_array() 
{ 
    throw BadCast("Element is not an StringArray"); 
}

StringArray const& 
ElementImplementation::as_string_array() const 
{ 
    throw BadCast("Element is not an StringArray"); 
}

IntegerArray&
ElementImplementation::as_integer_array() 
{ 
    throw BadCast("Element is not an IntegerArray"); 
}

IntegerArray const&
ElementImplementation::as_integer_array() const 
{ 
    throw BadCast("Element is not an IntegerArray"); 
}

RealArray&
ElementImplementation::as_real_array() 
{ 
    throw BadCast("Element is not an RealArray"); 
}

RealArray const&
ElementImplementation::as_real_array() const 
{ 
    throw BadCast("Element is not an RealArray"); 
}

BooleanArray&
ElementImplementation::as_boolean_array() 
{ 
    throw BadCast("Element is not an BooleanArray"); 
}

BooleanArray const&
ElementImplementation::as_boolean_array() const 
{ 
    throw BadCast("Element is not an BooleanArray"); 
}

String&
ElementImplementation::as_string() 
{ 
    throw BadCast("Element is not an String"); 
}

String const&
ElementImplementation::as_string() const 
{ 
    throw BadCast("Element is not an String"); 
}

Boolean& 
ElementImplementation::as_boolean() 
{ 
    throw BadCast("Element is not an Boolean"); 
}

Boolean const& 
ElementImplementation::as_boolean() const 
{ 
    throw BadCast("Element is not an Boolean"); 
}

Integer& 
ElementImplementation::as_integer() 
{ 
    throw BadCast("Element is not an Integer"); 
}

Integer const& 
ElementImplementation::as_integer() const 
{ 
    throw BadCast("Element is not an Integer"); 
}

Real& 
ElementImplementation::as_real() 
{ 
    throw BadCast("Element is not an Real"); 
}

Real const& 
ElementImplementation::as_real() const 
{ 
    throw BadCast("Element is not an Real"); 
}

Null& 
ElementImplementation::as_null() 
{ 
    throw BadCast("Element is not an Null"); 
}

Null const& 
ElementImplementation::as_null() const 
{ 
    throw BadCast("Element is not an Null"); 
}

}
