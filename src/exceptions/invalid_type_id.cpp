#include <PBD++/exceptions/invalid_type_id.h>
#include <sstream>

namespace PBD
{

namespace 
{
std::string
message(std::string const& where, TypeId::TypeId TypeId)
{
    std::ostringstream oss;
    oss << where << ": invalid_TypeId = " << TypeId;
    return oss.str();
}	
}

InvalidTypeId::InvalidTypeId(std::string const& where, TypeId::TypeId tid)
    : BOOST_IOSTREAMS_FAILURE(message(where, tid))
    , TypeId_(tid)
{
}

InvalidTypeId::~InvalidTypeId() throw()
{
}

TypeId::TypeId 
InvalidTypeId::type_id() const
{
    return TypeId_;
}

}
