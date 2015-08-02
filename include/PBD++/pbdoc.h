#ifndef PBD_PBDOC_H_
#define PBD_PBDOC_H_

#include <iosfwd>
#include <PBD++/pbdoc_head.h>
#include <PBD++/element.h>

namespace PBD
{

/**
 * Clase utilitaria que escribe un mensaje a un stream de salida.
 */
class PbDocWriter : boost::noncopyable
{
public:    
    PbDocWriter(Element const& body);
    
    /**
     * Metodo que escribe sobre el stream de salida pasado el contenido
     * del mensaje.
     * @throws PBD::InvalidSizeType
     */
    std::ostream& write(std::ostream& os);
    
    Element const& body() const;
    PBD::PbDocHead const& head() const;
    uint16_t crc_ccitt() const;
    
#ifndef PBD_UNIT_TEST_
	private:    
#else
	public:
#endif /*PBD_UNIT_TEST_*/

    Element const& body_;
    PBD::PbDocHead head_;
    uint16_t crc_ccitt_;    

    static std::vector<char> compress_body(std::vector<char> const& in);
};

class PbDoc
{
public:    
    PBD::PbDocHead const& get_head() const;
    Element const& get_body() const;    

private:    
    PBD::PbDocHead head_;
    Element body_;
    
    friend class PbDocReader;
};

/**
 * Clase utilitaria que lee un mensaje de un bloque de mensaje.
 */
class PbDocReader
{
public:    
    PbDocReader();
    
    void clear();

	/**
	 * @throws PBD::ParsingError
	 */      
    std::istream& one_step_read(std::istream& is); 
    
    std::size_t head_size();     
    
    /**
     * @throws PBD::ParsingError
     */      
    std::istream& read_head(std::istream& is);
    
    std::size_t body_size() const;
    
	/**
	 * @throws PBD::ParsingError
	 */      
    std::istream& read_body(std::istream& is);
    
    std::size_t checksum_size() const;

	/**
	 * @throws PBD::ParsingError
	 */      
    std::istream& read_checksum(std::istream& is);
    
    /**
     * @throws PBD::ChecksumError
     * @throws PBD::ParsingError
     */      
    PbDoc create_pbdoc();
    
    std::vector<char> const& buffer() const;
    
    uint16_t crc_ccitt() const;

	std::size_t buffer_size() const;
    
#ifndef PBD_UNIT_TEST_
	private:    
#else
	public:
#endif /*PBD_UNIT_TEST_*/

    PbDocHead head_;
    std::vector<char> buffer_;
    uint16_t crc_ccitt_;  

    static std::vector<char> decompress_body(std::vector<char> const& in);
};
	
}

#endif /*PBD_PBDOC_H_*/
