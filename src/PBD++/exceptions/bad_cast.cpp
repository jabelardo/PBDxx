#include <PBD++/exceptions/bad_cast.h>

namespace PBD
{

BadCast::BadCast(std::string const& what_arg)
    : std::runtime_error(what_arg)
{
}

BadCast::~BadCast() throw()
{
}

}
