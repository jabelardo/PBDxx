#include <PBD++/elements/boolean.h>
#include <PBD++/details/streams_operators.h>

namespace PBD
{

ElementImplementation::SharedPtr
Boolean::clone() const
{
    return SharedPtr(new Boolean(data_), ElementImplementation::destroy);
}

Boolean::Boolean(bool datum)
    : data_(datum)
{
}

Boolean::~Boolean()
{
}

bool 
Boolean::value() const
{
    return data_;
}

Boolean& 
Boolean::as_boolean()
{
    return *this;
}

Boolean const& 
Boolean::as_boolean() const
{
    return *this;    
}

TypeId::TypeId 
Boolean::type_id() const
{
    return TypeId::boolean; 
}
        
TypeId::TypeId 
Boolean::type_id_to_write() const
{
    return type_id();
}

void 
Boolean::read(std::istream& is, TypeId::TypeId)
{
    bool data;
    if (is >> Reader<bool>(data)) {
        data_ = data;
    }
}

void 
Boolean::write(std::ostream& os, TypeId::TypeId) const
{
    os << Writer<bool>(data_);
}

}
