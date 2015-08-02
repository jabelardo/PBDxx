#ifndef PBD_BOOLEAN_ARRAY_H_
#define PBD_BOOLEAN_ARRAY_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/elements/array.h>
#include <boost/dynamic_bitset.hpp>

namespace PBD
{

class BooleanArray : public PBD::ElementImplementation
                    , public Array<boost::dynamic_bitset<>, bool>
{
public:	    
	virtual BooleanArray& as_boolean_array();
    virtual BooleanArray const& as_boolean_array() const;
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
    
	BooleanArray();
    /**
 	 * @throws std::invalid_argument
 	 */
	BooleanArray(boost::dynamic_bitset<> const& set_to_copy);
	virtual ~BooleanArray();
	virtual SharedPtr clone() const;
};

}

#endif /*PBD_BOOLEAN_ARRAY_H_*/
