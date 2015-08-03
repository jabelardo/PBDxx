#ifndef PBDXX_INTEGER_H_
#define PBDXX_INTEGER_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/elements/number.h>

namespace PBD
{

class Integer : public PBD::ElementImplementation
              , public Number<int64_t>
{
public:
   	
    virtual Integer& as_integer();
    virtual Integer const& as_integer() const;
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

    Integer(int64_t datum = 0);
    ~Integer();
    virtual SharedPtr clone() const;
};

}

#endif /*PBDXX_INTEGER_H_*/
