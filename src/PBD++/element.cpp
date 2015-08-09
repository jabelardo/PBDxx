#include <PBD++/element.h>
#include <PBD++/exceptions/bad_cast.h>
#include <PBD++/exceptions/invalid_type_id.h>
#include <PBD++/details/streams_operators.h>
#include <PBD++/elements/element_implementation.h>
#include <PBD++/pbd.h>
#include <sstream>

namespace PBD
{

Element::ImplSharedPtr 
Element::implementation()  
{
    if (!implementation_) throw std::runtime_error("Element::implementation() : implementation_ es nulo");
    if (is_a_copy_) {
            implementation_ = implementation_->clone();
            is_a_copy_ = false;
    }
    return implementation_;
}

Element::ImplSharedPtr 
Element::implementation() const  
{
    if (!implementation_) throw std::runtime_error("Element::implementation() : implementation_ es nulo");
    return implementation_;
}

Element::Element(Element const& e)
    : implementation_(e.implementation_)
    , is_a_copy_(true)
{	
}

Element& 
Element::operator=(Element const& e)
{
    if (this != &e) {
        implementation_ = e.implementation_;
        is_a_copy_ = true;
    }
    return *this;
}

Element::Element(ImplSharedPtr const& impl)
    : implementation_(impl)
    , is_a_copy_(implementation_.use_count() > 1)
{
}

Element::Element(ElementImplementation const& impl)
    : implementation_(impl.clone())
    , is_a_copy_(false)
{
}


Element::Element()
    : implementation_(ImplSharedPtr(new Null, ElementImplementation::destroy))
    , is_a_copy_(false)
{
}

Element::~Element()
{
}

Element 
Element::clone() const
{
    ImplSharedPtr impl = implementation()->clone();
    return Element(impl);
}

void 
Element::swap(Element& e)
{
    if (this != &e) {
        implementation_.swap(e.implementation_);
        bool this_is_a_copy = is_a_copy_;
        is_a_copy_ = e.is_a_copy_;
        e.is_a_copy_ = this_is_a_copy;
    }
}

void 
Element::read(std::istream& is, TypeId::TypeId type)
{
    implementation()->read(is, type);
}
   
void 
Element::write(std::ostream& os, TypeId::TypeId type) const
{
    implementation()->write(os, type);    
}
    
TypeId::TypeId 
Element::type_id() const
{
    return implementation()->type_id();
    
}

TypeId::TypeId 
Element::type_id_to_write() const
{
    return implementation()->type_id_to_write();   
}

ElementMap&
Element::as_element_map() 
{ 
    return implementation()->as_element_map();
}

ElementMap const&
Element::as_element_map() const 
{  
    return implementation()->as_element_map();
}

ElementArray&
Element::as_element_array() 
{  
    return implementation()->as_element_array();
}

ElementArray const&
Element::as_element_array() const 
{ 
    return implementation()->as_element_array(); 
}

StringArray& 
Element::as_string_array() 
{ 
    return implementation()->as_string_array(); 
}

StringArray const& 
Element::as_string_array() const 
{ 
    return implementation()->as_string_array(); 
}

IntegerArray&
Element::as_integer_array() 
{ 
    return implementation()->as_integer_array(); 
}

IntegerArray const&
Element::as_integer_array() const 
{ 
    return implementation()->as_integer_array(); 
}

RealArray&
Element::as_real_array() 
{ 
    return implementation()->as_real_array(); 
}

RealArray const&
Element::as_real_array() const 
{ 
    return implementation()->as_real_array(); 
}

BooleanArray&
Element::as_boolean_array() 
{ 
	return implementation()->as_boolean_array(); 
}

BooleanArray const&
Element::as_boolean_array() const 
{ 
	return implementation()->as_boolean_array(); 
}

String&
Element::as_string() 
{ 
    return implementation()->as_string(); 
}

String const&
Element::as_string() const 
{ 
    return implementation()->as_string(); 
}

Boolean& 
Element::as_boolean() 
{ 
    return implementation()->as_boolean(); 
}

Boolean const& 
Element::as_boolean() const 
{ 
    return implementation()->as_boolean(); 
}

Integer& 
Element::as_integer() 
{ 
    return implementation()->as_integer(); 
}

Integer const& 
Element::as_integer() const 
{ 
    return implementation()->as_integer(); 
}

Real& 
Element::as_real() 
{ 
    return implementation()->as_real(); 
}

Real const& 
Element::as_real() const 
{ 
    return implementation()->as_real(); 
}

Null& 
Element::as_null() 
{ 
    return implementation()->as_null(); 
}

Null const& 
Element::as_null() const 
{ 
    return implementation()->as_null(); 
}

Element 
Element::create_string(std::string const& datum)
{
    ImplSharedPtr impl(new String(datum), ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_boolean(bool datum)
{
    ImplSharedPtr impl(new Boolean(datum), ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_null()
{
    ImplSharedPtr impl(new Null, ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_integer(int64_t datum)
{
    ImplSharedPtr impl(new Integer(datum), ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_real(double datum)
{
    ImplSharedPtr impl(new Real(datum), ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_string_array()
{
    ImplSharedPtr impl(new StringArray, ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_string_array(std::vector<std::string> const& vector_to_copy)
{
    ImplSharedPtr impl(new StringArray(vector_to_copy), ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_boolean_array()
{
    ImplSharedPtr impl(new BooleanArray, ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_boolean_array(boost::dynamic_bitset<> const& set_to_copy)
{
    ImplSharedPtr impl(new BooleanArray(set_to_copy), ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_integer_array()
{
    ImplSharedPtr impl(new IntegerArray, ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_integer_array(std::vector<int64_t> const& vector_to_copy)
{
    ImplSharedPtr impl(new IntegerArray(vector_to_copy), ElementImplementation::destroy);
    return Element(impl);
}
    
Element 
Element::create_real_array()
{
    ImplSharedPtr impl(new RealArray, ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_real_array(std::vector<double> const& vector_to_copy)
{
    ImplSharedPtr impl(new RealArray(vector_to_copy), ElementImplementation::destroy);
    return Element(impl);
}

Element 
Element::create_element_array()
{
    ImplSharedPtr impl(new ElementArray, ElementImplementation::destroy);
    return Element(impl);    
}

Element 
Element::create_element_array(std::vector<Element> const& vector_to_copy)
{
    ImplSharedPtr impl(new ElementArray(vector_to_copy), ElementImplementation::destroy);
    return Element(impl);    
}

Element 
Element::create_element_map(StringElementMap const& map_to_copy)
{
    ImplSharedPtr impl(new ElementMap(map_to_copy), ElementImplementation::destroy);
    return Element(impl); 	
}

Element 
Element::create_element_map()
{
    ImplSharedPtr impl(new ElementMap, ElementImplementation::destroy);
    return Element(impl); 
}

Element 
Element::create(TypeId::TypeId type)
{
    TypeId::TypeId adjusted_type_id = TypeId::from_read(type);

    switch (adjusted_type_id) {

        case TypeId::boolean_array:
            return create_boolean_array();

        case TypeId::int8_array:
        case TypeId::uint8_array:
        case TypeId::int16_array:
        case TypeId::uint16_array:
        case TypeId::int32_array:
        case TypeId::uint32_array:
        case TypeId::int64_array:
            return create_integer_array();

        case TypeId::float_array:
        case TypeId::double_array:
            return create_real_array();

        case TypeId::string_array:
            return create_string_array();

        case TypeId::element_array:
            return create_element_array();

        case TypeId::element_map:
            return create_element_map();

        case TypeId::string:
            return create_string();

        case TypeId::boolean:
            return create_boolean();

        case TypeId::int8_scalar:
        case TypeId::uint8_scalar:
        case TypeId::int16_scalar:
        case TypeId::uint16_scalar:
        case TypeId::int32_scalar:
        case TypeId::uint32_scalar:
        case TypeId::int64_scalar:
            return create_integer();

        case TypeId::float_scalar:
        case TypeId::double_scalar:
            return create_real();

        case TypeId::null:
            return create_null();

        default:
            break;
    }
    throw InvalidTypeId("PBD::Element::create", adjusted_type_id);
}

std::ostream& operator<<(std::ostream& os, Element const& e)
{
    TypeId::TypeId const type_id = e.type_id_to_write();    
    if (os << Writer<uint8_t>(static_cast<uint8_t>(type_id))) {
        e.write(os, type_id);
    }
    return os;
}

std::istream& operator>>(std::istream& is, Element& e)
{
    uint8_t type_id_raw = TypeId::unknown;
    if (is >> Reader<uint8_t>(type_id_raw)) {
        TypeId::TypeId const type_id = TypeId::TypeId(type_id_raw);
        e = Element::create(type_id);
        e.read(is, type_id);
    }
    return is;
}

}
