#include <PBD++/elements/string_array.h>
#include <PBD++/details/streams_operators.h>

namespace PBD
{

ElementImplementation::SharedPtr
StringArray::clone() const
{
    return SharedPtr(new StringArray(data_), ElementImplementation::destroy);
}

StringArray::StringArray()
{
}

StringArray::StringArray(std::vector<std::string> const& vector_to_copy)
	: Array<std::vector<std::string>, std::string>(vector_to_copy)
{
}
	
StringArray::~StringArray()
{
}
    
StringArray& 
StringArray::as_string_array()
{
	return *this;
}

StringArray const& 
StringArray::as_string_array() const
{
	return *this;
}

TypeId::TypeId 
StringArray::type_id() const
{
    return TypeId::string_array;
}
        
TypeId::TypeId 
StringArray::type_id_to_write() const
{
    return TypeId::to_write(type_id(), data_.size());
}

void 
StringArray::read(std::istream& is, TypeId::TypeId)
{
    is >> StringVectorReader(data_);
}
    
void 
StringArray::write(std::ostream& os, TypeId::TypeId) const
{
    os << StringVectorWriter(data_);
}

}
