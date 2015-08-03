#ifndef PBDXX_STREAMS_OPERATORS_H_
#define PBDXX_STREAMS_OPERATORS_H_

#include <iostream>
#include <vector>
#include <string>
#include <PBD++/details/cstdint.h>
#include <PBD++/streams.h>

namespace PBD {

template <typename T>
struct Writer : boost::noncopyable
{
    Writer(T v) : value_(v) {}
    T const value_;
};

template <typename T>	
std::ostream& operator<<(std::ostream& os, Writer<T> const& w)
{
    char const* buffer = reinterpret_cast<char const*>(&w.value_);
    os.write(buffer, sizeof(w.value_));
    return os;
}

template <typename T>
struct Reader
#ifdef _MSC_VER
    : boost::noncopyable
#endif
{
    Reader(T& v) : value_(v) {}
    T& value_;
};

template <typename T>
void fix_endianess(T& value)
{
    BOOST_STATIC_ASSERT(sizeof(T) == 0);
}

template <> void fix_endianess(bool&);
template <> void fix_endianess(uint8_t&);
template <> void fix_endianess(int8_t&);
template <> void fix_endianess(uint16_t&);
template <> void fix_endianess(int16_t&);
template <> void fix_endianess(uint32_t&);
template <> void fix_endianess(int32_t&);
template <> void fix_endianess(int64_t&);
template <> void fix_endianess(float&);
template <> void fix_endianess(double&);

template <typename T>	
FilterInStream& operator>>(FilterInStream& is, Reader<T> r)
{
    char* buffer = reinterpret_cast<char*>(&r.value_);	
    is.read(buffer, sizeof(r.value_));
    if (is.endianess() != Endianess::arch_endian) {
        fix_endianess(r.value_);
    }
    return is;
}

template <typename T>   
std::istream& operator>>(std::istream& is, Reader<T> r)
{
    char* buffer = reinterpret_cast<char*>(&r.value_);  
    return is.read(buffer, sizeof(r.value_));
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct ArrayWriter : boost::noncopyable
{
    ArrayWriter(T const* a, std::size_t s) : array_(a), size_(s) {}
    T const* array_;
    std::size_t const size_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, ArrayWriter<T> const& w)
{
    char const* buffer = reinterpret_cast<char const*>(w.array_);	
    os.write(buffer, sizeof(T) * w.size_);
    return os;
}

template <typename T>
struct ArrayReader
{
    ArrayReader(T* a, std::size_t s) : array_(a), size_(s) {}
    T* array_;
    std::size_t size_;
};

template <typename T>
void fix_endianess(T* array, std::size_t size)
{
    BOOST_STATIC_ASSERT(sizeof(T) == 0);
}

template <> void fix_endianess(bool*, std::size_t size);
template <> void fix_endianess(char*, std::size_t size);
template <> void fix_endianess(uint8_t*, std::size_t size);
template <> void fix_endianess(int8_t*, std::size_t size);
template <> void fix_endianess(uint16_t*, std::size_t size);
template <> void fix_endianess(int16_t*, std::size_t size);
template <> void fix_endianess(uint32_t*, std::size_t size);
template <> void fix_endianess(int32_t*, std::size_t size);
template <> void fix_endianess(int64_t*, std::size_t size);
template <> void fix_endianess(float*, std::size_t size);
template <> void fix_endianess(double*, std::size_t size);

template <typename T>
FilterInStream& operator>>(FilterInStream& is, ArrayReader<T> r)
{
    char* buffer = reinterpret_cast<char*>(r.array_);	
    is.read(buffer, sizeof(T) * r.size_);
    if (is.endianess() != Endianess::arch_endian) {
        fix_endianess(r.array_, r.size_);
    }
    return is;
}

template <typename T>
std::istream& operator>>(std::istream& is, ArrayReader<T> r)
{
    char* buffer = reinterpret_cast<char*>(r.array_);   
    return is.read(buffer, sizeof(T) * r.size_);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct VectorWriter : boost::noncopyable
{
    VectorWriter(std::vector<T> const& v) : vector_(v) {}
    std::vector<T> const& vector_;    
};

/**
 * @throws PBD::InvalidSizeType
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, VectorWriter<T> const& w)
{   
    os << Writer<uint16_t>(static_cast<uint16_t>(w.vector_.size()));

    if (w.vector_.size() > 0) {    
            os << ArrayWriter<T>(&w.vector_[0], w.vector_.size());
    }
    return os;
}

template <typename T>
struct VectorReader
#ifdef _MSC_VER
    : boost::noncopyable
#endif
{
    VectorReader(std::vector<T>& v) : vector_(v) {}
    std::vector<T>& vector_;
};

/**
 * @throws PBD::InvalidSizeType
 */
template <typename T>
std::istream& operator>>(std::istream& is, VectorReader<T> r)
{
    uint16_t size = 0;
    is >> Reader<uint16_t>(size);
    if (size > 0) {
            r.vector_.resize(size);
            is >> ArrayReader<T>(&r.vector_[0], r.vector_.size());
    }
    return is;
}

///////////////////////////////////////////////////////////////////////////////

struct StringVectorWriter : boost::noncopyable
{
    StringVectorWriter(std::vector<std::string> const& v);
    std::vector<std::string> const& vector_;
};

/**
 * @throws PBD::InvalidSizeType
 */
std::ostream& operator<<(std::ostream& os, StringVectorWriter const& w);

struct StringVectorReader
#ifdef _MSC_VER
    : boost::noncopyable
#endif
{
    StringVectorReader(std::vector<std::string>& v);
    std::vector<std::string>& vector_;
};

/**
 * @throws PBD::InvalidSizeType
 */
std::istream& operator>>(std::istream& is, StringVectorReader r);

} // namespace PBD

#endif /*PBDXX_STREAMS_OPERATORS_H_*/
