#ifndef PBD_REAL_ARRAY_H_
#define PBD_REAL_ARRAY_H_

#include <PBD++/elements/element_implementation.h>
#include <PBD++/elements/number_array.h>
#include <stdexcept>
#include <sstream>
#include <boost/math/special_functions/fpclassify.hpp>

namespace PBD
{

template<>
struct ArrayValidator<std::vector<double>, double>
{
	ArrayValidator() {}

	ArrayValidator(std::vector<double> const& data)
	{
		for (std::vector<double>::const_iterator i = data.begin(); i != data.end(); ++i) {
			(*this)(*i);
		}
	}

	void operator() (double const& datum)
	{
		if (boost::math::isnan(datum)) {
			std::ostringstream oss;
			oss << "RealArrayValidator::operator(): " << datum << " invalid argument";
			throw std::invalid_argument(oss.str());
		}
	}
};

class RealArray : public PBD::ElementImplementation
			     , public NumberArray<double>
{
public:    
	virtual RealArray& as_real_array();
    virtual RealArray const& as_real_array() const;
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

	RealArray();

    /**
 	 * @throws std::invalid_argument
 	 */
	RealArray(std::vector<double> const& set_to_copy);

	virtual ~RealArray();
    virtual SharedPtr clone() const;
};

}

#endif /*PBD_REAL_ARRAY_H_*/
