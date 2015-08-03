#include <PBD++/elements/element_map.h>
#include <PBD++/details/streams_operators.h>
#include <PBD++/exceptions/duplicate_key.h>

namespace PBD
{

ElementImplementation::SharedPtr 
ElementMap::clone() const
{
    return SharedPtr(new ElementMap(data_), ElementImplementation::destroy);
}

ElementMap::ElementMap()
    : data_()
{
}

ElementMap::ElementMap(Data const& map_to_copy)
    : data_(map_to_copy)
{
}

ElementMap::~ElementMap()
{
}

std::size_t 
ElementMap::size() const
{
    return data_.size();
}

Element const& 
ElementMap::operator[](std::string const& key) const
{
    Data::const_iterator iter = data_.find(key);
    return iter->second;
}

Element const& 
ElementMap::at(std::string const& key) const
{
    Data::const_iterator iter = data_.find(key);
    if (iter == data_.end()) {
        throw std::out_of_range("ElementMap::at: " + key + " out of range");
    }
    return iter->second;
}

std::vector<std::string> 
ElementMap::keys() const
{
    std::vector<std::string> result;
    for (Data::const_iterator iter = data_.begin(); iter != data_.end(); ++iter)
        result.push_back(iter->first);
    return result;
}

bool 
ElementMap::insert(std::string const& key, Element const& value)
{
    return data_.insert(std::make_pair(key, value)).second;
}

bool 
ElementMap::insert(std::string const& key, ElementImplementation const& value)
{
    return insert(key, value.clone());
}

bool  
ElementMap::insert(std::string const& key, ElementImplementation::SharedPtr const& value)
{
    return data_.insert(std::make_pair(key, value)).second;    
}

ElementMap::Data const&
ElementMap::value() const
{
    return data_;
}

ElementMap&
ElementMap::as_element_map()
{
    return *this;
}

ElementMap const&
ElementMap::as_element_map() const
{
    return *this;
}

TypeId::TypeId 
ElementMap::type_id() const
{
    return TypeId::element_map;
}

TypeId::TypeId 
ElementMap::type_id_to_write() const
{
    return TypeId::to_write(type_id(), data_.size());
}

void 
ElementMap::read(std::istream& is, TypeId::TypeId)
{
    std::vector<std::string> keys;    
    is >> StringVectorReader(keys);
    if (!is) return;
    
    std::vector<Element> values;
    values.reserve(keys.size());    
    for (std::size_t i = 0, size = keys.size(); i < size; ++i) {            
        Element e;
        is >> e;
        if (!is) return;
        values.push_back(e);        
    }
    
    Data new_data;
    for (std::size_t i = 0, size = keys.size(); i < size; ++i) {        
        if (!new_data.insert(std::make_pair(keys[i], values[i])).second ) {            
            throw DuplicateKey("ElementMap::read", keys[i]);
        }
    }
    data_.swap(new_data);
}
    
void 
ElementMap::write(std::ostream& os, TypeId::TypeId) const
{    	
    std::vector<std::string> keys;
    std::vector<Element> values;

    for (Data::const_iterator datum = data_.begin();
         datum != data_.end(); ++datum) {
        keys.push_back(datum->first);
        values.push_back(datum->second);
    }

    if (os << StringVectorWriter(keys)) {
        for (std::vector<Element>::const_iterator datum = values.begin();
             datum != values.end(); ++datum) {
            os << *datum;            
            if (!os) break;
        }
    }
}

}
