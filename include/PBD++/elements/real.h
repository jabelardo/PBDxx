#ifndef PBDXX_REAL_H_
#define PBDXX_REAL_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/elements/number.h>

namespace PBD
{

class Real : public PBD::ElementImplementation
           , public Number<double>
{
public:   	
    virtual Real& as_real();
    virtual Real const& as_real() const;
    virtual TypeId::TypeId type_id() const;      
    virtual TypeId::TypeId type_id_to_write() const;
    
    /**
     * @throws PBD::InvalidTypeId
     */      
    virtual void read(std::istream& is, TypeId::TypeId type);
    
    /**
     * @throws PBD::InvalidTypeId
     */          
    virtual void write(std::ostream& os, TypeId::TypeId type) const;
    
    Real(double datum = 0);
    ~Real();
    virtual SharedPtr clone() const;
};

}

#endif /*PBDXX_REAL_H_*/
