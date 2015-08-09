#include <PBD++/details/streams_operators.h>
#include <PBD++/details/type_id.h>
#include <boost/detail/endian.hpp>

namespace PBD
{

template <>
void fix_endianess(bool&) 
{
    // DO NOTHING
}

template <>
void fix_endianess(uint8_t&) 
{
    // DO NOTHING
}

template <>
void fix_endianess(int8_t&) 
{    
    // DO NOTHING
}

template <>
void fix_endianess(uint16_t& value) 
{
    uint16_t val = value;
    uint16_t tmp = ((0x00FF & (val >> 8))
                 |  (0xFF00 & (val << 8)));
    value = tmp;
}

template <>
void fix_endianess(int16_t& value) 
{
    uint16_t val = value;
    fix_endianess(val);
    value = val;
}

template <>
void fix_endianess(uint32_t& value) 
{
    uint32_t val = value;
    uint32_t tmp = ((0x000000FF & (val >> 24))
                 |  (0x0000FF00 & (val >> 8))
                 |  (0x00FF0000 & (val << 8))
                 |  (0xFF000000 & (val << 24)));
    value = tmp;
}

template <>
void fix_endianess(int32_t& value) 
{
    uint32_t val = value;
    fix_endianess(val);
    value = val;
}

template <>
void fix_endianess(uint64_t& value)
{
	int64_t val = value;

	int64_t tmp = ((0x00000000000000FFLL & (val >> 56))
                    |  (0x000000000000FF00LL & (val >> 40))
                    |  (0x0000000000FF0000LL & (val >> 24))
                    |  (0x00000000FF000000LL & (val >> 8))
                    |  (0x000000FF00000000LL & (val << 8))
                    |  (0x0000FF0000000000LL & (val << 24))
                    |  (0x00FF000000000000LL & (val << 40))
                    |  (0xFF00000000000000LL & (val << 56)));

	value = tmp;
}

template <>
void fix_endianess(int64_t& value)
{
    uint64_t val = value;
    fix_endianess(val);
    value = val;
}

template <>
void fix_endianess(float& value) 
{
    uint32_t val = reinterpret_cast<uint32_t*>(&value)[0];
    fix_endianess(val);
    reinterpret_cast<uint32_t*>(&value)[0] = val; 
}

template <>
void fix_endianess(double& value) 
{
    uint64_t val = reinterpret_cast<uint64_t*>(&value)[0];
    fix_endianess(val);
    reinterpret_cast<uint64_t*>(&value)[0] = val;
}

template <> 
void fix_endianess(bool*, std::size_t) 
{
    // DO NOTHING
}

template <> 
void fix_endianess(char*, std::size_t) 
{
    // DO NOTHING
}

template <> 
void fix_endianess(uint8_t*, std::size_t) 
{
    // DO NOTHING
}

template <> 
void fix_endianess(int8_t*, std::size_t) 
{
    // DO NOTHING
}

template <> 
void fix_endianess(uint16_t* array, std::size_t size) 
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

template <> 
void fix_endianess(int16_t* array, std::size_t size) 
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

template <> 
void fix_endianess(uint32_t* array, std::size_t size) 
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

template <> 
void fix_endianess(int32_t* array, std::size_t size) 
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

template <> 
void fix_endianess(int64_t* array, std::size_t size) 
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

template <> 
void fix_endianess(uint64_t* array, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

template <>
void fix_endianess(float* array, std::size_t size) 
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

template <> 
void fix_endianess(double* array, std::size_t size) 
{
    for (std::size_t i = 0; i < size; ++i) {
        fix_endianess(array[i]);
    }
}

StringVectorWriter::StringVectorWriter(std::vector<std::string> const& v)
    : vector_(v)
{     
}

std::ostream& operator<<(std::ostream& os, StringVectorWriter const& w)
{
    if (os << Writer<uint16_t>(static_cast<uint16_t>(w.vector_.size()))) {
        
        for (std::vector<std::string>::const_iterator datum = w.vector_.begin();
             datum != w.vector_.end(); ++datum) {           
            
            TypeId::TypeId datum_TypeId = TypeId::to_write(TypeId::string, datum->length());
            os << Writer<uint8_t>(static_cast<uint8_t>(datum_TypeId));
            
            std::vector<char> buffer(datum->begin(), datum->end());         
            os << VectorWriter<char>(buffer);
            
            if (!os) break;
        }
    }
    return os;
}

StringVectorReader::StringVectorReader(std::vector<std::string>& v)
    : vector_(v)
{     
}

std::istream& operator>>(std::istream& is, StringVectorReader r)
{    
    uint16_t size = 0;
    if (is >> Reader<uint16_t>(size)) {
        std::vector<std::string> data;
        for (std::size_t i = 0; i < size; ++i) {
                                    
            uint8_t datum_TypeId_raw;
            is >> Reader<uint8_t>(datum_TypeId_raw);
            if (!is) break;
                                                
            std::vector<char> buffer;
            is >> VectorReader<char>(buffer);
            if (!is) break;
            
            data.push_back(std::string(buffer.begin(), buffer.end()));
        }
        r.vector_.swap(data);
    }
    return is;
}

}
