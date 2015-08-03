#ifndef PBDXX_CHECKSUM_ERROR_H_
#define PBDXX_CHECKSUM_ERROR_H_

#include <stdexcept>
#include <PBD++/details/cstdint.h>

namespace PBD
{

class ChecksumError : public std::runtime_error
{
public:
    ChecksumError(std::string const& where, uint16_t crc_wanted, uint16_t crc_gotten);
    virtual ~ChecksumError() throw();

    uint16_t crc_wanted() const;
    uint16_t crc_gotten() const;

private:
    uint16_t crc_wanted_;
    uint16_t crc_gotten_;	
};

}

#endif /*PBDXX_CHECKSUM_ERROR_H_*/
