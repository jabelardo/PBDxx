#include <PBD++/exceptions/checksum_error.h>
#include <sstream>

namespace PBD
{

namespace 
{
std::string 
message(std::string const& where, uint16_t crc_wanted, uint16_t crc_gotten)
{
	std::ostringstream oss;
    oss << where << ": checksum_error: " <<  crc_wanted << " != " << crc_gotten;
	return oss.str();
}	
}

ChecksumError::ChecksumError(std::string const& where, uint16_t crc_wanted, uint16_t crc_gotten)
    : std::runtime_error(message(where, crc_wanted, crc_gotten))
    , crc_wanted_(crc_wanted)
    , crc_gotten_(crc_gotten)
{
}

ChecksumError::~ChecksumError() throw()
{
}

uint16_t 
ChecksumError::crc_wanted() const
{
	return crc_wanted_;
}

uint16_t 
ChecksumError::crc_gotten() const
{
	return crc_gotten_;
}

}
