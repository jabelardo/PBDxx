#include <PBD++/elements/null.h>
#include <PBD++/details/type_id.h>

namespace PBD
{

ElementImplementation::SharedPtr
Null::clone() const
{
    return SharedPtr(new Null, ElementImplementation::destroy);
}

Null::Null()
{
}

Null::~Null()
{
}

Null& 
Null::as_null()
{
    return *this;
}

Null const& 
Null::as_null() const
{
    return *this;
}

TypeId::TypeId 
Null::type_id() const
{
    return TypeId::null; 
}
  
TypeId::TypeId 
Null::type_id_to_write() const
{
    return type_id();
}

void 
Null::read(std::istream&, TypeId::TypeId)
{
}
    
void 
Null::write(std::ostream&, TypeId::TypeId) const
{
}

}
