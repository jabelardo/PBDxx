#include <PBD++/elements/real_array.h>
#include <PBD++/details/type_id.h>
#include <PBD++/exceptions/invalid_type_id.h>

namespace PBD
{

ElementImplementation::SharedPtr
RealArray::clone() const
{
    return SharedPtr(new RealArray(value()), ElementImplementation::destroy);
}

RealArray::RealArray()
    : NumberArray<double>()
{
}

RealArray::RealArray(std::vector<double> const& vector_to_copy)
    : NumberArray<double>(vector_to_copy)
{
}
	
RealArray::~RealArray()
{
}

RealArray&
RealArray::as_real_array()
{
    return *this;
}

RealArray const&
RealArray::as_real_array() const
{
    return *this;
}

TypeId::TypeId 
RealArray::type_id() const
{
    return TypeId::real_array;
}
 
TypeId::TypeId 
RealArray::type_id_to_write() const
{
    std::pair<DataType, DataType> range = data_range();
    return TypeId::best_real_array(range.first, range.second);
}

void 
RealArray::read(std::istream& is, TypeId::TypeId type)
{
    switch (type) {
    	case TypeId::float_array:
    		NumberArrayType::read<float>(is);
    		return;    	
    	
    	case TypeId::double_array:
    		NumberArrayType::read<double>(is);
    		return;
    	
        default:
        	throw InvalidTypeId("PBD::RealArray::read", type);
    }
}    

void 
RealArray::write(std::ostream& os, TypeId::TypeId type) const
{
    switch (type) {
    	case TypeId::float_array:
    		NumberArrayType::write<float>(os);
    		return;    	    	
    	
    	case TypeId::double_array:
    		NumberArrayType::write<double>(os);
    		return;    	
    	    	
        default:
        	throw InvalidTypeId("PBD::RealArray::write", type);
    }
}

}
