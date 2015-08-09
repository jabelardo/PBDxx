#include <PBD++/elements/integer_array.h>
#include <PBD++/details/type_id.h>
#include <PBD++/exceptions/invalid_type_id.h>

namespace PBD
{

ElementImplementation::SharedPtr
IntegerArray::clone() const
{
    return SharedPtr(new IntegerArray(value()), ElementImplementation::destroy);
}

IntegerArray::IntegerArray()
    : NumberArray<int64_t>()
{
}

IntegerArray::IntegerArray(std::vector<int64_t> const& vector_to_copy)
    : NumberArray<int64_t>(vector_to_copy)
{
}
	
IntegerArray::~IntegerArray()
{
}

IntegerArray&
IntegerArray::as_integer_array()
{
    return *this;
}

IntegerArray const&
IntegerArray::as_integer_array() const
{
    return *this;
}

TypeId::TypeId 
IntegerArray::type_id() const
{
    return TypeId::integer_array;
}

TypeId::TypeId 
IntegerArray::type_id_to_write() const
{
    std::pair<DataType, DataType> range = data_range();
    return TypeId::best_integer_array(range.first, range.second);
}

void 
IntegerArray::read(std::istream& is, TypeId::TypeId type)
{
    switch (type) {
    	case TypeId::uint8_array:
    		NumberArrayType::read<uint8_t>(is);
    		return;
    	
    	case TypeId::int8_array:
    		NumberArrayType::read<int8_t>(is);
    		return;
    	
    	case TypeId::uint16_array:
    		NumberArrayType::read<uint16_t>(is);
    		return;
    	
    	case TypeId::int16_array:
    		NumberArrayType::read<int16_t>(is);
    		return;
    	
    	case TypeId::uint32_array:
    		NumberArrayType::read<uint32_t>(is);
    		return;
    	
    	case TypeId::int32_array:
    		NumberArrayType::read<int32_t>(is);
    		return;
    	
    	case TypeId::int64_array:
    		NumberArrayType::read<int64_t>(is);
    		return;
    	
        default:
        	throw InvalidTypeId("PBD::IntegerArray::read", type);
    }
}    

void 
IntegerArray::write(std::ostream& os, TypeId::TypeId type) const
{
    switch (type) {
    	case TypeId::uint8_array:
    		NumberArrayType::write<uint8_t>(os);
    		return;    	
    	
    	case TypeId::int8_array:
    		NumberArrayType::write<int8_t>(os);
    		return;    	
    	
    	case TypeId::uint16_array:
    		NumberArrayType::write<uint16_t>(os);
    		return;    	
    	
    	case TypeId::int16_array:
    		NumberArrayType::write<int16_t>(os);
    		return;    	
    	
    	case TypeId::uint32_array:
    		NumberArrayType::write<uint32_t>(os);
    		return;    	
    	
    	case TypeId::int32_array:
    		NumberArrayType::write<int32_t>(os);
    		return;    	
    	
    	case TypeId::int64_array:
    		NumberArrayType::write<int64_t>(os);
    		return;    	
    	    	
        default:
        	throw InvalidTypeId("PBD::IntegerArray::write", type);
    }
}

}
