#include <PBD++/elements/element_array.h>
#include <PBD++/details/streams_operators.h>

namespace PBD
{

ElementImplementation::SharedPtr 
ElementArray::clone() const
{
    return SharedPtr(new ElementArray(data_), ElementImplementation::destroy);
}

ElementArray::ElementArray()
{
}

ElementArray::ElementArray(std::vector<Element> const& vector_to_copy)
	: Array<std::vector<Element>, Element>(vector_to_copy)
{
}

ElementArray::~ElementArray()
{
}

void 
ElementArray::push_back(Element const& e)
{
    Array<std::vector<Element>, Element>::push_back(e);
}

void 
ElementArray::push_back(ElementImplementation const& datum)
{
    push_back(datum.clone());
}

void 
ElementArray::push_back(ElementImplementation::SharedPtr const& datum)
{
    data_.push_back(Element(datum));
}

ElementArray&
ElementArray::as_element_array()
{
    return *this;
}

ElementArray const&
ElementArray::as_element_array() const
{
    return *this;
}

TypeId::TypeId 
ElementArray::type_id() const
{
    return TypeId::element_array;
}

TypeId::TypeId 
ElementArray::type_id_to_write() const
{
    return TypeId::to_write(type_id(), data_.size());
}

void 
ElementArray::read(std::istream& is, TypeId::TypeId)
{
    uint16_t size = 0;
    if (is >> Reader<uint16_t>(size)) {
        for (std::size_t i = 0; i < size; ++i) {

            Element e;
            is >> e;
            if (!is)
                break;

            data_.push_back(e);
        }
    }
}

void 
ElementArray::write(std::ostream& os, TypeId::TypeId) const
{
    if (os << Writer<uint16_t>(static_cast<uint16_t>(data_.size()))) {

        for (std::vector<Element>::const_iterator datum = data_.begin(); 
             datum != data_.end(); ++datum) {

            os << *datum;

            if (!os)
                break;
        }
    }
}

}
