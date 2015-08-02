#include <PBD++/pbdoc_head.h>
#include <PBD++/details/streams_operators.h>
#include <sstream>
#include <stdexcept>
#include <PBD++/exceptions/size_out_of_range.h>

namespace PBD
{

PbDocHead::PbDocHead()
    : flags_(INIT_FLAGS | PbDocHeadFlags::UNCOMPRESSED_FLAG)
    , body_size_(0)
{    
}

void
PbDocHead::clear()
{
    flags_ = INIT_FLAGS | PbDocHeadFlags::UNCOMPRESSED_FLAG;
    body_size_ = 0;
}

PbDocHead::PbDocHead(PbDocHead const& h)
    : flags_(h.flags_)
    , body_size_(h.body_size_)
{    
}

PbDocHead
PbDocHead::createUncompressed(uint32_t body_size)
{
    PbDocHead head;
    head.flags_ = INIT_FLAGS | PbDocHeadFlags::UNCOMPRESSED_FLAG;
    head.body_size_ = body_size;
    return head;
}

PbDocHead
PbDocHead::createCompressed(uint32_t body_size)
{
    PbDocHead head;
    head.flags_ = INIT_FLAGS | PbDocHeadFlags::COMPRESSED_FLAG;
    head.body_size_ = body_size;
    return head;
}

PbDocHead::PbDocHead(Flags const& f)
    : flags_(f)
    , body_size_(0)
{    
}

PbDocHead::~PbDocHead()
{
}

PbDocHead& 
PbDocHead::operator=(PbDocHead const& h)
{
    if (this != &h) {
        flags_ = h.flags_;
        body_size_ = h.body_size_;
    }
    return *this;
}

PbDocHead::Flags const PbDocHead::INIT_FLAGS = PbDocHeadFlags::VERSION
#ifdef BOOST_LITTLE_ENDIAN
                                             | PbDocHeadFlags::LITTLE_ENDIAN_FLAG;
#else
                                             | PbDocHeadFlags::BIG_ENDIAN_FLAG;
#endif

void 
PbDocHead::read(std::istream& is)
{
    uint8_t raw_flags;
    is >> PBD::Reader<uint8_t>(raw_flags);
    if (!is) return;
    
    Flags new_flags = Flags(raw_flags);

    uint32_t new_body_size;
    is >> PBD::Reader<uint32_t>(new_body_size);
    if (!is) return;
    
    flags_ = new_flags;
    body_size_ = new_body_size;
}

std::size_t 
PbDocHead::body_size_size()
{
    return sizeof(uint32_t);    
}

std::size_t 
PbDocHead::flags_size()
{  
    return sizeof(uint8_t);
}

void 
PbDocHead::write(std::ostream& os) const
{
    (os << PBD::Writer<uint8_t>(static_cast<uint8_t>(flags_.to_ulong()))) 
        && (os << PBD::Writer<uint32_t>(body_size_));    
}

uint32_t 
PbDocHead::body_size() const
{
    return body_size_;
}

uint8_t 
PbDocHead::version() const
{
    Flags f = flags_ & PbDocHeadFlags::VERSION_MASK;
    return static_cast<uint8_t>(f.to_ulong());
}

bool 
PbDocHead::is_compressed() const
{
    Flags f = flags_ & PbDocHeadFlags::COMPRESS_MASK;
    return static_cast<bool>(f.to_ulong() != 0);

}

Endianess::Endianess 
PbDocHead::endianess() const
{
    Flags f = flags_ & PbDocHeadFlags::ENDIAN_MASK;
    return Endianess::Endianess(f.to_ulong() > 0);
}

std::ostream& 
operator<<(std::ostream& os, PbDocHead const& h)
{
    h.write(os);
    return os;
}

std::istream& 
operator>>(std::istream& is, PbDocHead& h)
{
    h.read(is);
    return is;    
}

}
