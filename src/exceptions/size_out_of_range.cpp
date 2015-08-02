#include <PBD++/exceptions/size_out_of_range.h>
#include <sstream>

namespace PBD
{

namespace 
{
std::string
message(std::string const& where, std::size_t size_wanted)
{
	std::ostringstream oss;
    oss << where << ": size_out_of_range: " <<  size_wanted << " > 16777216UL";
	return oss.str();
}	
}

SizeOutOfRange::SizeOutOfRange(std::string const& where, uint16_t size_wanted)
    : std::out_of_range(message(where, size_wanted))
    , size_wanted_(size_wanted)
{
}

SizeOutOfRange::~SizeOutOfRange() throw()
{
}

uint16_t 
SizeOutOfRange::size_wanted() const
{
	return size_wanted_;
}

}
