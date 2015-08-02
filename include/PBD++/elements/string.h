#ifndef PBD_STRING_H_
#define PBD_STRING_H_

#include <PBD++/elements/element_implementation.h>
#include <string>
 
namespace PBD
{

/**
 * Clase que define los elementos de string.
 * Para referencia a los metodos virtuales ver documentacion de la clase ElementImplementation.
 */
class String : public PBD::ElementImplementation
{
public:	
	/**
     * Devuelve la data del elemento.
     * @return un std::string que es una copia de la data del elemento.
     */
    std::string value() const;
    
	virtual String& as_string();
	virtual String const& as_string() const;
	virtual TypeId::TypeId type_id() const;		
	virtual TypeId::TypeId type_id_to_write() const;
	virtual void read(std::istream& is, TypeId::TypeId type);    
	virtual void write(std::ostream& os, TypeId::TypeId type) const;
	
	String(std::string const& datum = "");
    virtual ~String();
    virtual SharedPtr clone() const;
    
private:
    std::string data_;
};

}

#endif /*PBD_STRING_H_*/
