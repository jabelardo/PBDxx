#include <pbd/pbdxx.h>
#include <cassert>

#include "element.h"
#include "pbdconf_internal.h"

namespace pbdxx {
    
typedef std::shared_ptr<pbd_element> element_ptr;

element::element(std::shared_ptr<pbd_element> const& impl)
: conf(pbd_default_conf), impl(impl) {
}

element::element(pbd_conf conf, std::shared_ptr<pbd_element> const& impl)
: conf(conf), impl(impl) {
}

element element::from_buffer(std::vector<char> const& buffer, size_t& read_bytes) {
    return from_buffer(pbd_default_conf, buffer, read_bytes);
}
        
element element::from_buffer(pbd_conf conf, std::vector<char> const& buffer, size_t& read_bytes) {
    pbd_element* e = pbd_element_from_buffer_custom(conf, &buffer[0], &read_bytes);
    return element(conf, element_ptr(e));
}

int element::to_buffer(std::vector<char>& buffer) {
    char* raw_buffer = 0;
    size_t size = 0;
    int result = pbd_element_to_buffer_custom(conf, impl.get(), &raw_buffer, &size);
    if (result == 0) {
        std::vector<char> to_swap(raw_buffer, raw_buffer + size);
        buffer.swap(to_swap);
    }
    conf.free_mem(raw_buffer);
    return result;
}

pbd_type_id element::type() const {
    return pbd_element_type(impl.get());
}

boolean element::boolean() const {
    assert(type() == pbd_type_bool);
    struct boolean s;
    s.impl = this->impl;
    return s;
}

boolean_array element::boolean_array() const {
    assert(type() == pbd_type_bool_array);
    struct boolean_array s;
    s.impl = this->impl;
    return s;
}

integer element::integer() const {
    assert(type() == pbd_type_integer);
    struct integer s;
    s.impl = this->impl;
    return s;
}

integer_array element::integer_array() const {
    assert(type() == pbd_type_integer_array);
    struct integer_array s;
    s.impl = this->impl;
    return s;
}

null element::null() const {
    assert(type() == pbd_type_null);
    struct null s;
    s.impl = this->impl;
    return s;
}

real element::real() const {
    assert(type() == pbd_type_real);
    struct real s;
    s.impl = this->impl;
    return s;
}

real_array element::real_array() const {
    assert(type() == pbd_type_real_array);
    struct real_array s;
    s.impl = this->impl;
    return s;
}

string element::string() const {
    assert(type() == pbd_type_string);
    struct string s;
    s.impl = this->impl;
    return s;
}

null::null() 
: element(element_ptr(pbd_null_new(), pbd_element_free)) {
}

null::null(pbd_conf conf) 
: element(conf, element_ptr(pbd_null_new_custom(conf), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}
        
boolean::boolean(bool value) 
: element(element_ptr(pbd_bool_create(value), pbd_element_free)) {
}
        
boolean::boolean(pbd_conf conf, bool value) 
: element(conf, element_ptr(pbd_bool_create_custom(conf, value), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}
        
bool boolean::get() const {    
    return pbd_bool_get(impl.get());
}

void boolean::set(bool value) {
    pbd_bool_set(impl.get(), value);
}

integer::integer(int64_t value) 
: element(element_ptr(pbd_integer_create(value), pbd_element_free)) {
}
        
integer::integer(pbd_conf conf, int64_t value) 
: element(conf, element_ptr(pbd_integer_create_custom(conf, value), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}
        
int64_t integer::get() const {    
    return pbd_integer_get(impl.get());
}

void integer::set(int64_t value) {
    pbd_integer_set(impl.get(), value);
}

real::real(double value) 
: element(element_ptr(pbd_real_create(value), pbd_element_free)) {
}
        
real::real(pbd_conf conf, double value) 
: element(conf, element_ptr(pbd_real_create_custom(conf, value), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}
        
double real::get() const {    
    return pbd_real_get(impl.get());
}

void real::set(double value) {
    pbd_real_set(impl.get(), value);
}

string::string(std::string const& value) 
: element(element_ptr(pbd_string_create(value.c_str()), pbd_element_free)) {
}
        
string::string(pbd_conf conf, std::string const& value) 
: element(conf, element_ptr(pbd_string_create_custom(conf, value.c_str()), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}
        
std::string string::get() const {    
    return pbd_string_get(impl.get());
}

void string::set(std::string const& value) {
    pbd_string_set(impl.get(), value.c_str());
}

boolean_array::boolean_array() 
: element(element_ptr(pbd_bool_array_new(), pbd_element_free)) {
}

boolean_array::boolean_array(pbd_conf conf) 
: element(conf, element_ptr(pbd_bool_array_new_custom(conf), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}

int boolean_array::add(bool value) {
    return pbd_bool_array_add_custom(conf, impl.get(), value);
}

size_t boolean_array::size() const {
    return pbd_bool_array_size(impl.get());
}

std::vector<bool> boolean_array::values() const {
    int length = size();
    if (length > 0) {
        const bool* values = pbd_bool_array_values(impl.get());
        return std::vector<bool>(values, values + length);
    } else {
        return std::vector<bool>();
    }
    
}

element_array::element_array() 
: element(element_ptr(pbd_element_array_new(), pbd_element_free)) {
}

element_array::element_array(pbd_conf conf) 
: element(conf, element_ptr(pbd_element_array_new_custom(conf), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}

int element_array::add(element const& value) {
    // NOTE: This vector is needed basically to increase the ref counter of the 
    //       internal shared_ptr
    elements.push_back(value);
    return pbd_element_array_add_custom(conf, impl.get(), value.impl.get());
}

size_t element_array::size() const {
    return pbd_element_array_size(impl.get());
}

std::vector<element> element_array::values() const {
    return elements;
}

integer_array::integer_array() 
: element(element_ptr(pbd_integer_array_new(), pbd_element_free)) {
}

integer_array::integer_array(pbd_conf conf) 
: element(conf, element_ptr(pbd_integer_array_new_custom(conf), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}

int integer_array::add(int64_t value) {
    return pbd_integer_array_add_custom(conf, impl.get(), value);
}

size_t integer_array::size() const {
    return pbd_integer_array_size(impl.get());
}

std::vector<int64_t> integer_array::values() const {
    int length = size();
    if (length > 0) {
        const int64_t* values = pbd_integer_array_values(impl.get());
        return std::vector<int64_t>(values, values + length);
    } else {
        return std::vector<int64_t>();
    }
}

real_array::real_array() 
: element(element_ptr(pbd_real_array_new(), pbd_element_free)) {
}

real_array::real_array(pbd_conf conf) 
: element(conf, element_ptr(pbd_real_array_new_custom(conf), 
          [conf](const pbd_element* e){ pbd_element_free_custom(conf, e); })) {
}

int real_array::add(double value) {
    return pbd_real_array_add_custom(conf, impl.get(), value);
}

size_t real_array::size() const {
    return pbd_real_array_size(impl.get());
}

std::vector<double> real_array::values() const {
    int length = size();
    if (length > 0) {
        const double* values = pbd_real_array_values(impl.get());
        return std::vector<double>(values, values + length);
    } else {
        return std::vector<double>();
    }
}

}
