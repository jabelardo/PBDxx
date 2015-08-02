#include <PBD++/exceptions/duplicate_key.h>
#include <sstream>

namespace PBD
{

namespace 
{
std::string
message(std::string const& where, std::string const& key)
{
	std::ostringstream oss;
    oss << where << ": duplicate_key = '" << key << "'";
	return oss.str();
}	
}

DuplicateKey::DuplicateKey(std::string const& where, std::string const& key)
    : BOOST_IOSTREAMS_FAILURE(message(where, key))
    , key_(key)
{
}

DuplicateKey::~DuplicateKey() throw()
{
}

std::string 
DuplicateKey::key() const
{
	return key_;
}

}
