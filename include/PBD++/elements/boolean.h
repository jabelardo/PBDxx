#ifndef PBDXX_BOOLEAN_H_
#define PBDXX_BOOLEAN_H_

#include <PBD++/elements/element_implementation.h>

namespace PBD
{
/**
 * Clase que define los elementos de Boolean.
 * Para referencia a los metodos virtuales ver documentacion de la clase ElementImplementation.
 */
class Boolean : public PBD::ElementImplementation
{
public:
    /**
     * Devuelve la data del elemento.
     * @return un bool que es una copia de la data del elemento.
     */
    bool value() const;
		
    virtual Boolean& as_boolean();
    virtual Boolean const& as_boolean() const;
    virtual TypeId::TypeId type_id() const;
    virtual TypeId::TypeId type_id_to_write() const;
    virtual void read(std::istream& is, TypeId::TypeId type);    
    virtual void write(std::ostream& os, TypeId::TypeId type) const;
    
    Boolean(bool datum = false);
    virtual ~Boolean();
    virtual SharedPtr clone() const;
    
private:
    bool data_;	
};

}

#endif /*PBDXX_BOOLEAN_H_*/
