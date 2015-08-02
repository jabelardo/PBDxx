#include <PBD++/elements/real.h>
#include <PBD++/details/type_id.h>
#include <PBD++/exceptions/invalid_type_id.h>

namespace PBD
{

ElementImplementation::SharedPtr
Real::clone() const
{
    return SharedPtr(new Real(data_), ElementImplementation::destroy);
}

Real::Real(double datum)
	: Number<double>(datum)
{
}

Real::~Real()
{
}
   	
Real& 
Real::as_real()
{
	return *this;
}

Real const& 
Real::as_real() const
{
	return *this;
}

TypeId::TypeId 
Real::type_id() const
{
    return TypeId::real;
}

TypeId::TypeId 
Real::type_id_to_write() const
{
    return TypeId::best_real(data_);
}

void 
Real::read(std::istream& is, TypeId::TypeId type)
{
    switch (type) {
    	case TypeId::float_scalar: 
    		NumberType::read<float>(is);
        	return;
    	
    	case TypeId::double_scalar: 
    		NumberType::read<double>(is);
        	return;
    	
        default:
            throw InvalidTypeId("PBD::Real::read", type);
    }
}
    
void 
Real::write(std::ostream& os, TypeId::TypeId type) const
{
    switch (type) {
    	case TypeId::float_scalar:
        	os << Writer<float>(static_cast<const float>(data_));
        	return;
    	
    	case TypeId::double_scalar:
        	os << Writer<double>(data_);
        	return;
    	
        default:
            throw InvalidTypeId("PBD::Real::write", type);
    }
}
    
}
