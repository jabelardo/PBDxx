#ifndef PBD_PBDOC_HEAD_H_
#define PBD_PBDOC_HEAD_H_

#include <bitset>
#include <PBD++/streams.h>
#include <string>
#include <PBD++/details/cstdint.h>
#include <PBD++/details/endianess.h>

namespace PBD
{

namespace PbDocHeadFlags
{

typedef std::bitset<8> Flags;

/**
 * Constantes para el manejo de las banderas, indican la cantidad de bytes que se
 * usan para registrar el endiness del mensaje y la VERSION del mensaje
 */

 /**
  * Version
  */
Flags const VERSION            = Flags(std::string("00000001"));
Flags const VERSION_MASK       = Flags(std::string("00111111"));

/**
 * Endiness
 */
Flags const BIG_ENDIAN_FLAG    = Flags(std::string("00000000"));
Flags const LITTLE_ENDIAN_FLAG = Flags(std::string("01000000"));
Flags const ENDIAN_MASK        = Flags(std::string("01000000"));


/**
 * Compress
 */
Flags const COMPRESSED_FLAG    = Flags(std::string("10000000"));
Flags const UNCOMPRESSED_FLAG  = Flags(std::string("00000000"));
Flags const COMPRESS_MASK      = Flags(std::string("10000000"));

} // namespace HeadFlags

class PbDocHead
{
public:
    typedef PbDocHeadFlags::Flags Flags;
    
    PbDocHead();
    PbDocHead(Flags const& f);
    PbDocHead(PbDocHead const& h);
	static PbDocHead createCompressed(uint32_t body_size);
	static PbDocHead createUncompressed(uint32_t body_size);
	~PbDocHead();
	
	PbDocHead& operator=(PbDocHead const& h);
  
	void read(std::istream& is);
	
	void write(std::ostream& os) const;
	
    std::size_t flags_size();
    
    std::size_t body_size_size();   

	uint32_t body_size() const;

	uint8_t version() const;

	Endianess::Endianess endianess() const;

    void clear();

    bool is_compressed() const;
    
#ifndef PBD_UNIT_TEST_
	private:    
#else
	public:
#endif /*PBD_UNIT_TEST_*/

    Flags flags_;
    uint32_t body_size_;
     
    static Flags const INIT_FLAGS;
};

std::ostream& operator<<(std::ostream& os, PbDocHead const& h);
std::istream& operator>>(std::istream& is, PbDocHead& h);

}

#endif /*PBD_PBDOC_HEAD_H_*/
