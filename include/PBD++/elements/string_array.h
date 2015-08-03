#ifndef PBDXX_STRING_ARRAY_H_
#define PBDXX_STRING_ARRAY_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/elements/array.h>
#include <string>
#include <vector>

namespace PBD
{

class StringArray : public PBD::ElementImplementation
                  , public Array<std::vector<std::string>, std::string>
{
public:    
    virtual StringArray& as_string_array();
    virtual StringArray const& as_string_array() const;
    virtual TypeId::TypeId type_id() const;
    virtual TypeId::TypeId type_id_to_write() const;
    virtual void read(std::istream& is, TypeId::TypeId type);    
    virtual void write(std::ostream& os, TypeId::TypeId type) const;
    
    StringArray();
    /**
    * @throws std::invalid_argument
    */
   StringArray(std::vector<std::string> const& vector_to_copy);
   virtual ~StringArray();
    virtual SharedPtr clone() const;
};

}

#endif /*PBDXX_STRING_ARRAY_H_*/
