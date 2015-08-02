#include <PBD++/elements/integer.h>
#include <PBD++/details/type_id.h>
#include <PBD++/exceptions/invalid_type_id.h>

namespace PBD
{

ElementImplementation::SharedPtr
Integer::clone() const
{
    return SharedPtr(new Integer(data_), ElementImplementation::destroy);
}

Integer::Integer(int64_t datum)
	: Number<int64_t>(datum)
{
}

Integer::~Integer()
{
}
    
Integer& 
Integer::as_integer()
{
	return *this;
}

Integer const& 
Integer::as_integer() const
{
	return *this;
}

TypeId::TypeId 
Integer::type_id() const
{
    return TypeId::integer;
}
            
TypeId::TypeId 
Integer::type_id_to_write() const
{
    return TypeId::best_integer(data_);
}

void 
Integer::read(std::istream& is, TypeId::TypeId type)
{
    switch (type) {
    	
    	case TypeId::int8_scalar: 
    		NumberType::read<int8_t>(is);
        	return;
    	
    	case TypeId::uint8_scalar: 
    		NumberType::read<uint8_t>(is);
        	return;        	
    	
		case TypeId::int16_scalar: 
    		NumberType::read<int16_t>(is);
        	return;        	
    	
		case TypeId::uint16_scalar: 
    		NumberType::read<uint16_t>(is);
        	return;        	
    	
		case TypeId::int32_scalar: 
    		NumberType::read<int32_t>(is);
        	return;        	
    	
		case TypeId::uint32_scalar: 
    		NumberType::read<uint32_t>(is);
        	return;        	
    	
		case TypeId::int64_scalar: 
    		NumberType::read<int64_t>(is);
        	return;        	
    	
        default:
            throw InvalidTypeId("PBD::Integer::read", type);
    }
}
    
void 
Integer::write(std::ostream& os, TypeId::TypeId type) const
{
    switch (type) {
        case TypeId::int8_scalar:
        	os << Writer<int8_t>(static_cast<const int8_t>(data_));
        	return;            

        case TypeId::uint8_scalar:
        	os << Writer<uint8_t>(static_cast<const uint8_t>(data_));
        	return;  

        case TypeId::int16_scalar:
        	os << Writer<int16_t>(static_cast<const int16_t>(data_));
        	return;  

        case TypeId::uint16_scalar:
        	os << Writer<uint16_t>(static_cast<const uint16_t>(data_));
        	return;  

        case TypeId::int32_scalar:
        	os << Writer<int32_t>(static_cast<const int32_t>(data_));
        	return;  

        case TypeId::uint32_scalar:
        	os << Writer<uint32_t>(static_cast<const uint32_t>(data_));
        	return;  

        case TypeId::int64_scalar:
        	os << Writer<int64_t>(data_);
        	return;  

        default:
            throw InvalidTypeId("PBD::Integer::write", type);
    }
}

}
