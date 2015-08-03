#ifndef PBDXX_NULL_H_
#define PBDXX_NULL_H_

#include <PBD++/elements/element_implementation.h>

namespace PBD
{

class Null : public PBD::ElementImplementation
{
public:
    virtual Null& as_null();
    virtual Null const& as_null() const;
    virtual TypeId::TypeId type_id() const; 
    virtual TypeId::TypeId type_id_to_write() const;
    virtual void read(std::istream& is, TypeId::TypeId type);    
    virtual void write(std::ostream& os, TypeId::TypeId type) const;
    virtual SharedPtr clone() const;
    
    Null();
    virtual ~Null();
};

}

#endif /*PBDXX_NULL_H_*/
