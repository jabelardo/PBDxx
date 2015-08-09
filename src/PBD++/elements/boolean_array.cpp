#include <PBD++/elements/boolean_array.h>
#include <PBD++/details/streams_operators.h>
#include <PBD++/details/dynamic_bitset.h>

namespace PBD
{

ElementImplementation::SharedPtr
BooleanArray::clone() const
{
    return SharedPtr(new BooleanArray(data_), ElementImplementation::destroy);
}

BooleanArray::BooleanArray()
{
}

BooleanArray::BooleanArray(boost::dynamic_bitset<> const& set_to_copy)
    : Array<boost::dynamic_bitset<>, bool>(set_to_copy)
{
}
	
BooleanArray::~BooleanArray()
{
}

BooleanArray&
BooleanArray::as_boolean_array()
{
    return *this;
}

BooleanArray const&
BooleanArray::as_boolean_array() const
{
    return *this;
}

TypeId::TypeId 
BooleanArray::type_id() const
{
    return TypeId::boolean_array;
}
 
TypeId::TypeId 
BooleanArray::type_id_to_write() const
{
    std::size_t const raw_data_size = (data_.size() / 8) 
                                    + (data_.size() % 8 != 0);
    
    return TypeId::to_write(type_id(), raw_data_size);
}

void 
BooleanArray::read(std::istream& is, TypeId::TypeId)
{
    uint16_t size = 0;
    is >> Reader<uint16_t>(size);
    if (!is) return;
        
    uint8_t datum_type_id_raw;
    is >> Reader<uint8_t>(datum_type_id_raw);
    if (!is) return;
    
    std::vector<uint8_t> raw_data;
    
    if (is >> VectorReader<uint8_t>(raw_data)) {
        data_ = DynamicBitset::from_uint8_vector(raw_data);
        data_.resize(size, false);
    }
}
    
void 
BooleanArray::write(std::ostream& os, TypeId::TypeId) const
{
    if (os << Writer<uint16_t>(static_cast<uint16_t>(data_.size()))) {
        
        std::vector<uint8_t> const raw_data = DynamicBitset::to_uint8_vector(data_);
        
        TypeId::TypeId raw_data_type_id = TypeId::to_write(TypeId::uint8_array, raw_data.size());
        
        os << Writer<uint8_t>(static_cast<uint8_t>(raw_data_type_id));
        
        os << VectorWriter<uint8_t>(raw_data);
    }
}

}
