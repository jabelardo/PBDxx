#include <pbd/pbdxx.h>
#include <pbd/pbddoc.h>
#include <cassert>

#include "element.h"

namespace pbdxx {
    
bad_cast_exception::bad_cast_exception(const std::string& what)
    : std::runtime_error(what) {
}

bad_cast_exception::~bad_cast_exception() throw() {
}
    
void element_base::destroy(element_base* e_impl) {
    if (e_impl->destroy_impl) {
        if (e_impl->impl) {
            pbd_element_free_custom(e_impl->conf, e_impl->impl);
        }
        delete e_impl;
    }
}

element_base::~element_base() {
}

pbd_type_id element_base::type() const {
    return impl->vtable->type;
}

pbd_conf element_base::config() const {
    return conf;
}
    
element_base::element_base(pbd_element* impl, bool destroy_impl, pbd_conf conf)
    : impl(impl), destroy_impl(destroy_impl), conf(conf) {
}
       
element_base* 
element_base::create(pbd_element* e, bool destroy_impl, pbd_conf conf) {
    pbd_type_id type = e->vtable->type;
    element_base* base = 0;
    switch (type) {
        case pbd_type_bool: {
            void* mem = conf.mem_alloc(sizeof(boolean));
            base = new (mem) boolean(e, destroy_impl, conf);
            break;
        }
        case pbd_type_bool_array: {
            void* mem = conf.mem_alloc(sizeof(boolean_array));
            base = new (mem) boolean_array(e, destroy_impl, conf);
            break;
        }
        case pbd_type_element_array: {
            void* mem = conf.mem_alloc(sizeof(element_array));
            base = new (mem) element_array(e, destroy_impl, conf);
            break;
        }
        case pbd_type_integer: {
            void* mem = conf.mem_alloc(sizeof(integer));
            base = new (mem) integer(e, destroy_impl, conf);
            break;
        }
        case pbd_type_integer_array: {
            void* mem = conf.mem_alloc(sizeof(integer_array));
            base = new (mem) integer_array(e, destroy_impl, conf);
            break;
        }
        case pbd_type_null: {
            void* mem = conf.mem_alloc(sizeof(null));
            base = new (mem) null(e, destroy_impl, conf);
            break;
        }
        case pbd_type_real: {
            void* mem = conf.mem_alloc(sizeof(real));
            base = new (mem) real(e, destroy_impl, conf);
            break;
        }
        case pbd_type_real_array: {
            void* mem = conf.mem_alloc(sizeof(real_array));
            base = new (mem) real_array(e, destroy_impl, conf);
            break;
        }
        case pbd_type_string: {
            void* mem = conf.mem_alloc(sizeof(string));
            base = new (mem) string(e, destroy_impl, conf);
            break;
        }
        default:
            break;
    }
    return base;
}

element_base* 
element_base::create(pbd_type_id type, pbd_conf conf) {
    pbd_element* e = pbd_element_new_custom(conf, type);
    return create(e, true, conf);
}

const boolean& element_base::as_boolean() const {
    throw bad_cast_exception("element_impl is not a boolean");     
} 

boolean& element_base::as_boolean() {    
    throw bad_cast_exception("element_impl is not a boolean");     
} 
        
const boolean_array& element_base::as_boolean_array() const {    
    throw bad_cast_exception("element_impl is not a boolean_array");     
}

boolean_array& element_base::as_boolean_array() {    
    throw bad_cast_exception("element_impl is not a boolean_array");     
}   
        
const element_array& element_base::as_element_array() const {    
    throw bad_cast_exception("element_impl is not an element_array");     
}

element_array& element_base::as_element_array() {    
    throw bad_cast_exception("element_impl is not an element_array");     
}  
        
const integer& element_base::as_integer() const {    
    throw bad_cast_exception("element_impl is not an integer");     
}

integer& element_base::as_integer() {    
    throw bad_cast_exception("element_impl is not an integer");     
}   
        
const integer_array& element_base::as_integer_array() const {    
    throw bad_cast_exception("element_impl is not an integer_array");     
}

integer_array& element_base::as_integer_array() {    
    throw bad_cast_exception("element_impl is not an integer_array");     
} 
        
const real& element_base::as_real() const {    
    throw bad_cast_exception("element_impl is not a real");     
}

real& element_base::as_real() {    
    throw bad_cast_exception("element_impl is not a real");     
}  
        
const real_array& element_base::as_real_array() const {    
    throw bad_cast_exception("element_impl is not a real_array");     
}  

real_array& element_base::as_real_array() {    
    throw bad_cast_exception("element_impl is not a real_array");     
}  
        
const string& element_base::as_string() const {    
    throw bad_cast_exception("element_impl is not a string");     
}  

string& element_base::as_string() {    
    throw bad_cast_exception("element_impl is not a string");     
}  

int element_base::to_buffer(std::vector<char>& buffer) {
    char* raw_buffer = 0;
    size_t size = 0;
    int result = pbd_element_to_buffer_custom(conf, impl, &raw_buffer, &size);
    if (result == 0) {
        std::vector<char> to_swap(raw_buffer, raw_buffer + size);
        buffer.swap(to_swap);
    }
    conf.free_mem(raw_buffer);
    return result;
}

int element::to_buffer(std::vector<char>& buffer) {
    return impl->to_buffer(buffer);
}

null::null(pbd_conf conf) 
    : element_base(pbd_null_new_custom(conf), true, conf) {
}

null::null(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
}
        
boolean::boolean(bool value, pbd_conf conf) 
    : element_base(pbd_bool_create_custom(conf, value), true, conf) {
}
        
boolean::boolean(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
}

bool boolean::get() const {    
    return pbd_bool_get(impl);
}

void boolean::set(bool value) {
    pbd_bool_set(impl, value);
}

const boolean& boolean::as_boolean() const {
    return *this;
}
        
boolean& boolean::as_boolean() {
    return *this;
}
        
integer::integer(int64_t value, pbd_conf conf) 
    : element_base(pbd_integer_create_custom(conf, value), true, conf) {
}
        
integer::integer(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
}
        
int64_t integer::get() const {    
    return pbd_integer_get(impl);
}

void integer::set(int64_t value) {
    pbd_integer_set(impl, value);
}

const integer& integer::as_integer() const {
    return *this;
}
        
integer& integer::as_integer() {
    return *this;
}
        
real::real(double value, pbd_conf conf) 
    : element_base(pbd_real_create_custom(conf, value), true, conf) {
}
        
real::real(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
} 

double real::get() const {    
    return pbd_real_get(impl);
}

void real::set(double value) {
    pbd_real_set(impl, value);
}

const real& real::as_real() const {
    return *this;
}
        
real& real::as_real() {
    return *this;
}
        
string::string(std::string const& value, pbd_conf conf) 
    : element_base(pbd_string_create_custom(conf, value.c_str()), true, conf) {
}
        
string::string(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
} 
        
std::string string::get() const {    
    return pbd_string_get(impl);
}

void string::set(std::string const& value) {
    pbd_string_set(impl, value.c_str());
}

const string& string::as_string() const {
    return *this;
}
        
string& string::as_string() {
    return *this;
}
        
boolean_array::boolean_array(pbd_conf conf) 
    : element_base(pbd_bool_array_new_custom(conf), true, conf) {
}
        
boolean_array::boolean_array(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
} 

int boolean_array::add(bool value) {
    return pbd_bool_array_add_custom(conf, impl, value);
}

size_t boolean_array::size() const {
    return pbd_bool_array_size(impl);
}

std::vector<bool> boolean_array::values() const {
    size_t impl_size = size();
    size_t booleans_size = booleans.size();
    if (impl_size != booleans_size) {
        booleans.clear();
        if (impl_size > 0) {
            const bool* values = pbd_bool_array_values(impl);
            booleans.insert(booleans.end(), values, values + impl_size);
        }
    }
    return booleans;
}

const boolean_array& boolean_array::as_boolean_array() const {
    return *this;
}
        
boolean_array& boolean_array::as_boolean_array() {
    return *this;
}
        
element_array::element_array(pbd_conf conf) 
    : element_base(pbd_element_array_new_custom(conf), true, conf) {
}
        
element_array::element_array(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
} 

int element_array::add(element const& value) {
    const pbd_element* v = value.impl->impl;
    return pbd_element_array_add_custom(conf, impl, v);
}

size_t element_array::size() const {
    return pbd_element_array_size(impl);
}

std::vector<element> element_array::values() const {
    size_t impl_size = size();
    size_t elements_size = elements.size();
    if (impl_size != elements_size) {
        elements.clear();
        if (impl_size > 0) {
            const pbd_element** values = pbd_element_array_values(impl);
            for (int i = 0; i < impl_size; ++i) {
                pbd_element* value = (pbd_element*) values[i];
                std::shared_ptr<element_base> shared_ptr(create(value, false, conf));
                elements.push_back(element(shared_ptr));
            }
        }
    }
    return elements;
}

const element_array& element_array::as_element_array() const {
    return *this;
}      

element_array& element_array::as_element_array() {
    return *this;
}
        
integer_array::integer_array(pbd_conf conf) 
    : element_base(pbd_integer_array_new_custom(conf), true, conf) {
}
        
integer_array::integer_array(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
} 

int integer_array::add(int64_t value) {
    return pbd_integer_array_add_custom(conf, impl, value);
}

size_t integer_array::size() const {
    return pbd_integer_array_size(impl);
}

std::vector<int64_t> integer_array::values() const {
    size_t impl_size = size();
    size_t integers_size = integers.size();
    if (impl_size != integers_size) {
        integers.clear();
        if (impl_size > 0) {
            const int64_t* values = pbd_integer_array_values(impl);
            integers.insert(integers.end(), values, values + impl_size);
        } 
    }
    return integers;
}

const integer_array& integer_array::as_integer_array() const {
    return *this;
}      

integer_array& integer_array::as_integer_array() {
    return *this;
}
        
real_array::real_array(pbd_conf conf) 
    : element_base(pbd_real_array_new_custom(conf), true, conf) {
}
        
real_array::real_array(pbd_element* impl, bool destroy_impl, pbd_conf conf) 
    : element_base(impl, destroy_impl, conf) {
} 

int real_array::add(double value) {
    return pbd_real_array_add_custom(conf, impl, value);
}

size_t real_array::size() const {
    return pbd_real_array_size(impl);
}

std::vector<double> real_array::values() const {
    size_t impl_size = size();
    size_t reals_size = reals.size();
    if (impl_size != reals_size) {
        reals.clear();
        if (impl_size > 0) {
        const double* values = pbd_real_array_values(impl);
        reals.insert(reals.end(), values, values + impl_size);
        } 
    }
    return reals;
}

const real_array& real_array::as_real_array() const {
    return *this;
}      

real_array& real_array::as_real_array() {
    return *this;
}

element::element(pbd_conf conf) 
    : impl(new null(conf)) {
}

element::element(pbd_type_id type, pbd_conf conf) 
    : impl(std::shared_ptr<element_base>(element_base::create(type, conf))) {
}
        
element::element(const std::shared_ptr<element_base>& impl)
    : impl(impl) {
}

element 
element::create_null(pbd_conf conf) {
    return element(pbd_type_null, conf);
}
        
element 
element::create_boolean(bool value, pbd_conf conf) {
    element e(pbd_type_bool, conf);
    e.as_boolean().set(value);
    return e;
}
        
element 
element::create_integer(int64_t value, pbd_conf conf) {
    element e(pbd_type_integer, conf);
    e.as_integer().set(value);
    return e;
}
        
element 
element::create_real(double value, pbd_conf conf) {
    element e(pbd_type_real, conf);
    e.as_real().set(value);
    return e;
}
        
element 
element::create_string(const std::string& value, pbd_conf conf) {
    element e(pbd_type_string, conf);
    e.as_string().set(value);
    return e;
}
        
element 
element::create_boolean_array(pbd_conf conf) {
    return element(pbd_type_bool_array, conf);
}
        
element 
element::create_integer_array(pbd_conf conf) {
    return element(pbd_type_integer_array, conf);
}
        
element 
element::create_real_array(pbd_conf conf) {
    return element(pbd_type_real_array, conf);
}
        
element 
element::create_element_array(pbd_conf conf) {
    return element(pbd_type_element_array, conf);
}
        
element element::from_buffer(std::vector<char> const& buffer, 
        size_t& read_bytes, pbd_conf conf) {
    pbd_element* e = 
            pbd_element_from_buffer_custom(conf, &buffer[0], &read_bytes);
    element_base* base = element_base::create(e, true, conf);
    return element(std::shared_ptr<element_base>(base));
}
        
pbd_type_id element::type() const {
    return impl->type();
}               

const boolean& element::as_boolean() const {
    return impl->as_boolean();
}

boolean& element::as_boolean() {
    return impl->as_boolean();
}

const boolean_array& element::as_boolean_array() const {
    return impl->as_boolean_array();
}

boolean_array& element::as_boolean_array() {
    return impl->as_boolean_array();
}

const element_array& element::as_element_array() const {
    return impl->as_element_array();
}

element_array& element::as_element_array() {
    return impl->as_element_array();
}

const integer& element::as_integer() const {
    return impl->as_integer();
}

integer& element::as_integer() {
    return impl->as_integer();
}

const integer_array& element::as_integer_array() const {
    return impl->as_integer_array();
}

integer_array& element::as_integer_array() {
    return impl->as_integer_array();
}

const real& element::as_real() const {
    return impl->as_real();
}

real& element::as_real() {
    return impl->as_real();
}

const real_array& element::as_real_array() const {
    return impl->as_real_array();
}

real_array& element::as_real_array() {
    return impl->as_real_array();
}

const string& element::as_string() const {
    return impl->as_string();
}

string& element::as_string() {
    return impl->as_string();
}

int element::to_doc_buffer(std::vector<char>& doc_buffer, pbd_conf conf) const {
    char* buffer = 0;
    size_t size = 0;
    int result = pbd_doc_to_buffer_custom(conf, impl->impl, &buffer, &size);
    doc_buffer.assign(buffer, buffer + size);
    return result;
}

int doc_buffer_valid_checksum(const std::vector<char>& doc_buffer) {
    return pbd_doc_valid_checksum(&doc_buffer[0]);
}

element element::from_doc_buffer(std::vector<char> const& buffer, 
        size_t& read_bytes, pbd_conf conf) {
    pbd_element* e = pbd_doc_from_buffer_custom(conf, &buffer[0], &read_bytes);
    element_base* base = element_base::create(e, true, conf);
    return element(std::shared_ptr<element_base>(base));
}

}
