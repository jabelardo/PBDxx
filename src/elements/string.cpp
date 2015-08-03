#include <PBD++/elements/string.h>
#include <PBD++/details/streams_operators.h>

namespace PBD
{

ElementImplementation::SharedPtr
String::clone() const
{
    return SharedPtr(new String(data_), ElementImplementation::destroy);
}

String::String(std::string const& datum)
    : data_(datum)
{
}

String::~String()
{
}

String&
String::as_string()
{ 
    return *this;
}

String const&
String::as_string() const
{ 
    return *this; 
}


TypeId::TypeId 
String::type_id() const
{
    return TypeId::string;
}

std::string 
String::value() const
{
    return data_;
}

TypeId::TypeId 
String::type_id_to_write() const
{
    return TypeId::to_write(type_id(), data_.size());
}

void 
String::read(std::istream& is, TypeId::TypeId)
{
    std::vector<char> char_vector;
    if (is >> VectorReader<char>(char_vector)) {
        if (char_vector.size() > 0) {
            data_.assign(&char_vector[0], char_vector.size());
        }
    }
}

void 
String::write(std::ostream& os, TypeId::TypeId) const
{
    std::vector<char> const char_vector(data_.begin(), data_.end());
    os << VectorWriter<char>(char_vector);
}

}
