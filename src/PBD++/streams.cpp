#include <PBD++/streams.h>
#include <boost/range/iterator_range.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace PBD
{

FilterOutStream::FilterOutStream(std::vector<char>& buffer)
    : boost::iostreams::filtering_ostream(boost::iostreams::back_inserter(buffer))
{
}

FilterInStream::FilterInStream(std::vector<char> const& buffer)
    : boost::iostreams::filtering_istream(boost::make_iterator_range(buffer))
    , endianess_(Endianess::arch_endian)
{
}

void 
FilterInStream::endianess(Endianess::Endianess endianess)
{
    endianess_ = endianess;
}

Endianess::Endianess 
FilterInStream::endianess() const
{
    return endianess_;
}

VectorCharSink::VectorCharSink(std::vector<char>& buffer)
    : buffer_(buffer)
{
}

std::streamsize
VectorCharSink::write(const char* s, std::streamsize n)
{
    buffer_.insert(buffer_.end(), s, s + n);
    return n;
}

VectorCharSource::VectorCharSource(std::vector<char>& buffer)
    : buffer_(buffer)
{
}
    
std::streamsize 
VectorCharSource::read(char* s, std::streamsize n)
{
    std::streamsize amt = static_cast<std::streamsize>(buffer_.size());
    std::streamsize result = std::min(n, amt);
    if (result != 0) {
        std::copy(buffer_.begin(), buffer_.begin() + result, s);
        buffer_.erase(buffer_.begin(), buffer_.begin() + result);
        return result;
    } else {
        return -1; // EOF
    }
}

}
