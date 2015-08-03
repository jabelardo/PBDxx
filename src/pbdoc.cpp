#include <PBD++/pbdoc.h>
#include <PBD++/streams.h>
#include <PBD++/details/streams_operators.h>
#include <sstream>
#include <iostream>
#include <PBD++/exceptions/checksum_error.h>
#include <PBD++/exceptions/parsing_error.h>
#include <zlib.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4245) // signed/unsigned mismatch
#include <boost/crc.hpp>
#pragma warning(pop)
#else
#include <boost/crc.hpp>
#endif

namespace PBD
{

PbDocWriter::PbDocWriter(Element const& body)
    : body_(body)
    , head_()
    , crc_ccitt_(0)
{
}

Element const& 
PbDocWriter::body() const
{
    return body_;
}

PBD::PbDocHead const&
PbDocWriter::head() const
{
    return head_;
}

uint16_t 
PbDocWriter::crc_ccitt() const
{
    return crc_ccitt_;
}

namespace
{
template<typename T>
std::vector<char> 
to_buffer(T const& t)
{
    std::vector<char> buffer;
    FilterOutStream out(buffer);
    out << t;    
    out.flush();
    return buffer;
}
}

std::ostream&
PbDocWriter::write(std::ostream& os)
{
    std::vector<char> body_buffer = to_buffer(body_);     
    
    std::vector<char> compress_body_buffer = compress_body(body_buffer);

    if (compress_body_buffer.size() < body_buffer.size()) {
        head_ = PbDocHead::createCompressed(compress_body_buffer.size());
        body_buffer.swap(compress_body_buffer);

    } else {
        head_ = PbDocHead::createUncompressed(body_buffer.size());
    }

    std::vector<char> const head_buffer = to_buffer(head_);        
    
    std::vector<char> buffer;
    buffer.reserve(head_buffer.size() + body_buffer.size());
    std::copy(head_buffer.begin(), head_buffer.end(), std::back_inserter(buffer));
    std::copy(body_buffer.begin(), body_buffer.end(), std::back_inserter(buffer));
    
    boost::crc_ccitt_type crc;
    crc.process_bytes(&buffer[0], buffer.size());
    crc_ccitt_ = static_cast<uint16_t>(crc.checksum());
#ifdef BOOST_BIG_ENDIAN
    {
        uint16_t crc_copy = crc_ccitt_;
        reinterpret_cast<uint8_t*>(&crc_ccitt_)[0] = reinterpret_cast<uint8_t*>(&crc_copy)[1];
        reinterpret_cast<uint8_t*>(&crc_ccitt_)[1] = reinterpret_cast<uint8_t*>(&crc_copy)[0];
    }
#endif
    os.write(&buffer[0], buffer.size()); 
    os << Writer<uint16_t>(crc_ccitt_);
    return os;
}

PBD::PbDocHead const&
PbDoc::get_head() const
{
    return head_;
}

PBD::Element const&
PbDoc::get_body() const
{
    return body_;
}

PbDocReader::PbDocReader()
    : head_()
    , buffer_()
    , crc_ccitt_(0)
{  
}

void 
PbDocReader::clear()
{
    head_.clear();
    buffer_.clear();
    crc_ccitt_ = 0;
}
    
std::size_t 
PbDocReader::head_size()
{
    return head_.flags_size() + head_.body_size_size(); 
}

std::istream& 
PbDocReader::read_head(std::istream& is)
{
    try {           		
        std::vector<char> head_buffer(head_size());
        if (is.read(&head_buffer[0], head_buffer.size())) {
            std::copy(head_buffer.begin(), head_buffer.end(), std::back_inserter(buffer_));
        }
        InVectorCharStream ivcs(head_buffer);
        ivcs >> head_;
        return is;
	    
    } catch (std::exception const& e) {
    	throw ParsingError("PbDocReader::read_body_size:", e);
    }  	    
}

std::size_t 
PbDocReader::body_size() const
{  
    return head_.body_size();
}

std::size_t 
PbDocReader::buffer_size() const
{
    return buffer_.size();
}

std::istream& 
PbDocReader::read_body(std::istream& is)
{
    try {      

    std::vector<char> body(body_size());
    if (is.read(&body[0], body.size())) {
        std::copy(body.begin(), body.end(), std::back_inserter(buffer_));
    }
    return is;
	    
    } catch (std::exception const& e) {
    	throw ParsingError("PbDocReader::read_body:", e);
    }  	    
}

std::size_t 
PbDocReader::checksum_size() const
{    
    return sizeof(uint16_t);
}

std::istream& 
PbDocReader::read_checksum(std::istream& is)
{
    try {      
		
        uint16_t crc;
        if (is >> Reader<uint16_t>(crc)) {
        #ifdef BOOST_BIG_ENDIAN
            reinterpret_cast<uint8_t*>(&crc_ccitt_)[0] = reinterpret_cast<uint8_t*>(&crc)[1];
            reinterpret_cast<uint8_t*>(&crc_ccitt_)[1] = reinterpret_cast<uint8_t*>(&crc)[0];
        #else            
            crc_ccitt_= crc;
        #endif
        }
        return is;
	    
    } catch (std::exception const& e) {
    	throw ParsingError("PbDocReader::read_checksum:", e);
    }  	    
}

std::istream& 
PbDocReader::one_step_read(std::istream& is)
{
    read_head(is) && read_body(is) && read_checksum(is);
    return is;
    	
}

std::vector<char> const& 
PbDocReader::buffer() const
{
    return buffer_;
}

uint16_t 
PbDocReader::crc_ccitt() const
{
    return crc_ccitt_;
}

PbDoc 
PbDocReader::create_pbdoc()
{  
    boost::crc_ccitt_type crc;
    crc.process_bytes(&buffer_[0], buffer_.size());
    if (crc_ccitt_ != crc.checksum()) {
        throw ChecksumError("PbDocReader::create_pbdoc", crc_ccitt_, crc.checksum());
    }

    buffer_.erase(buffer_.begin(), buffer_.begin() + head_size());

    if (head_.is_compressed()) {
        buffer_ = decompress_body(buffer_);
    }

    PbDoc pbdoc;
    FilterInStream in(buffer_);
    try {
        in.endianess(pbdoc.head_.endianess());
    	if (in >> pbdoc.body_) {    	
    	    return pbdoc;
    	}
    } catch (std::exception const& e) {
    	throw ParsingError("PbDocReader::create_pbdoc:", e);
    }    
    throw ParsingError("PbDocReader::create_pbdoc");
}

std::vector<char>
PbDocWriter::compress_body(std::vector<char> const& in)
{
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = deflateInit(&strm, 9);
    if (ret != Z_OK) throw std::runtime_error("zlib error");
    strm.avail_in = in.size();
    strm.next_in = (Bytef *)&in[0];

    size_t const CHUNK = 131072;
    unsigned char out[CHUNK];
    std::vector<char> result;
    do {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        deflate(&strm, Z_FINISH);
        unsigned have = CHUNK - strm.avail_out;
        result.reserve(have + result.size());
        std::copy(out, out + have, std::back_inserter(result));
    } while (strm.avail_out == 0);
    deflateEnd(&strm);
    return result;
}

std::vector<char>
PbDocReader::decompress_body(std::vector<char> const& in)
{
    z_stream strm;    
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    int ret = inflateInit(&strm);
    if (ret != Z_OK) throw std::runtime_error("zlib error");
    strm.avail_in = in.size();
    strm.next_in = (Bytef *)&in[0];

    size_t const CHUNK = 131072;
    unsigned char out[CHUNK];
    std::vector<char> result;
    do {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        ret = inflate(&strm, Z_NO_FLUSH);
        switch (ret) 
        {
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR;     /* and fall through */
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            inflateEnd(&strm);
            throw std::runtime_error("zlib error");
        }
        unsigned have = CHUNK - strm.avail_out;
        result.reserve(have + result.size());
        std::copy(out, out + have, std::back_inserter(result));
    } while (strm.avail_out == 0);
    inflateEnd(&strm);
    return result;
}

}
