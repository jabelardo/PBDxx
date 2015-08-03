#ifndef PBDXX_BAD_CAST_H_
#define PBDXX_BAD_CAST_H_

#include <stdexcept>

namespace PBD
{

class BadCast : public std::runtime_error
{
public:
    BadCast(std::string const& what_arg);
    virtual ~BadCast() throw();
};

}

#endif /*PBDXX_BAD_CAST_H_*/
