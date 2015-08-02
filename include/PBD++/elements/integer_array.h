#ifndef PBD_INTEGER_ARRAY_H_
#define PBD_INTEGER_ARRAY_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/elements/number_array.h>

namespace PBD
{

class IntegerArray : public ElementImplementation
					, public NumberArray<int64_t>
{
public:        
	virtual IntegerArray& as_integer_array();
    virtual IntegerArray const& as_integer_array() const;
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

	IntegerArray();
    /**
 	 * @throws std::invalid_argument
 	 */
	IntegerArray(std::vector<int64_t> const& set_to_copy);
	virtual ~IntegerArray();
    virtual SharedPtr clone() const;
};

}

#endif /*PBD_INTEGER_ARRAY_H_*/
