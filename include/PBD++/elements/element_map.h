#ifndef PBDXX_ELEMENT_MAP_H_
#define PBDXX_ELEMENT_MAP_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/element.h>
#include <string>
#include <utility>

namespace PBD
{

class ElementMap : public PBD::ElementImplementation
{
public:    

    bool insert(std::string const& key, Element const& value);
    bool insert(std::string const& key, ElementImplementation const& value);
    bool insert(std::string const& key, ElementImplementation::SharedPtr const& value);
	
    std::size_t size() const;
    
    Element const& operator[](std::string const& key) const;
    
    Element const& at(std::string const& key) const;
    
    std::vector<std::string> keys() const;
    
    typedef StringElementMap Data;
    
    /**
     * Copia en contenido del mapa
     */    
    Data const& value() const;
    
    virtual ElementMap& as_element_map();
    virtual ElementMap const& as_element_map() const;
    virtual TypeId::TypeId type_id() const;
    virtual TypeId::TypeId type_id_to_write() const;
    
    /**
     * @throws PBD::DuplicateKey
     */
    virtual void read(std::istream& is, TypeId::TypeId type);    
    
    virtual void write(std::ostream& os, TypeId::TypeId type) const;
    
    ElementMap();
    ElementMap(Data const& map_to_copy);
    virtual ~ElementMap();
    virtual SharedPtr clone() const;
    
private:        
    Data data_;    
};

}

#endif /*PBDXX_ELEMENT_MAP_H_*/
