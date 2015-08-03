#ifndef PBDXX_ELEMENT_ARRAY_H_
#define PBDXX_ELEMENT_ARRAY_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/elements/array.h>
#include <PBD++/element.h>
#include <vector>

namespace PBD
{

class ElementArray : public PBD::ElementImplementation
                   , public Array<std::vector<Element>, Element>
{
public:    
    /**
    * @throws std::invalid_argument
    */
    void push_back(Element const& element);
    /**
    * @throws std::invalid_argument
    */
    void push_back(ElementImplementation const& datum);
    /**
    * @throws std::invalid_argument
    */
    void push_back(ElementImplementation::SharedPtr const& datum);
    
    virtual ElementArray& as_element_array();
    virtual ElementArray const& as_element_array() const;
    virtual TypeId::TypeId type_id() const;
    virtual TypeId::TypeId type_id_to_write() const;
    
    /**
     * @throws PBD::InvalidSizeType
     */    
    virtual void read(std::istream& is, TypeId::TypeId type);    
    
    /**
    * @throws PBD::InvalidSizeType
    */
    virtual void write(std::ostream& os, TypeId::TypeId type) const;
    
    ElementArray();
    /**
    * @throws std::invalid_argument
    */
    ElementArray(std::vector<Element> const& vector_to_copy);
    virtual ~ElementArray();
    virtual SharedPtr clone() const;
};


}

#endif /*PBDXX_ELEMENT_ARRAY_H_*/
