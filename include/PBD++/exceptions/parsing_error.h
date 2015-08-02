#ifndef PBD_PARSING_ERROR_H_
#define PBD_PARSING_ERROR_H_

#include <stdexcept>

namespace PBD
{

class ParsingError : public std::runtime_error
{
public:
	ParsingError(std::string const& where);
	ParsingError(std::string const& where, std::runtime_error const& e);
	ParsingError(std::string const& where, std::logic_error const& e);
	ParsingError(std::string const& where, std::exception const& e);
	virtual ~ParsingError() throw();

};

}

#endif /*PBD_PARSING_ERROR_H_*/
