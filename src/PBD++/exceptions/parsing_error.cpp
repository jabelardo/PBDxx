#include <PBD++/exceptions/parsing_error.h>
#include <sstream>

namespace PBD
{

namespace 
{
std::string
message(std::string const& where, std::string const& except = "unknown", std::string const& what = "")
{
    std::ostringstream oss;	
    oss << where << ": ParsingError = (" << except << ")" << what;
    return oss.str();
}	
}

ParsingError::ParsingError(std::string const& where)
    : std::runtime_error(message(where))
{
}

ParsingError::ParsingError(std::string const& where, std::runtime_error const& e)
    : std::runtime_error(message(where, "std::runtime_error", e.what()))
{
}

ParsingError::ParsingError(std::string const& where, std::logic_error const& e)
    : std::runtime_error(message(where, "std::logic_error", e.what()))
{
}

ParsingError::ParsingError(std::string const& where, std::exception const& e)
    : std::runtime_error(message(where, "std::exception", e.what()))
{
}

ParsingError::~ParsingError() throw()
{
}

}
