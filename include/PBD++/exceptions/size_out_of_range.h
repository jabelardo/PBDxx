#ifndef PBD_SIZE_OUT_OF_RANGE_H_
#define PBD_SIZE_OUT_OF_RANGE_H_

#include <stdexcept>
#include <PBD++/details/cstdint.h>

namespace PBD
{

class SizeOutOfRange : public std::out_of_range
{
public:
	SizeOutOfRange(std::string const& where, uint16_t size_wanted);
	virtual ~SizeOutOfRange() throw();
	
	uint16_t size_wanted() const;

private:
	uint16_t size_wanted_;
};

}

#endif /*PBD_SIZE_OUT_OF_RANGE_H_*/
