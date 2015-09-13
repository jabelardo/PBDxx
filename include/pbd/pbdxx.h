/* 
 * File:   pbdxx.h
 * Author: jabelardo
 *
 * Created on September 12, 2015, 2:19 AM
 */

#ifndef PBDXX_H
#define	PBDXX_H

#include <memory>
#include <string>
#include <vector>
#include <pbd/pbd.h>

namespace pbdxx {

    struct boolean;
    struct boolean_array;
    struct element_array;
    struct integer;
    struct integer_array;
    struct null;
    struct real;
    struct real_array;
    struct string;
    
    struct element {
        static element from_buffer(std::vector<char> const& buffer, size_t& read_bytes);
        static element from_buffer(pbd_conf conf, std::vector<char> const& buffer, size_t& read_bytes);
        int to_buffer(std::vector<char>& buffer);
        pbd_type_id type() const;   
        boolean boolean() const;    
        boolean_array boolean_array() const;   
        integer integer() const;      
        integer_array integer_array() const;   
        null null() const;     
        real real() const;  
        real_array real_array() const;  
        string string() const;  
    protected: 
        element(std::shared_ptr<pbd_element> const& impl);
        element(pbd_conf conf, std::shared_ptr<pbd_element> const& impl);
        pbd_conf conf;
        std::shared_ptr<pbd_element> impl;
        friend struct element_array;
    };
    
    struct null : public element {
        null();
        null(pbd_conf conf);
    };
    
    struct boolean : public element {
        boolean(bool value = false);
        boolean(pbd_conf conf, bool value = false);
        bool get() const;
        void set(bool value);
    };
    
    struct integer : public element {
        integer(int64_t value = 0);
        integer(pbd_conf conf, int64_t value = 0);
        int64_t get() const;
        void set(int64_t value);
    };
    
    struct real : public element {
        real(double value = 0);
        real(pbd_conf conf, double value = 0);
        double get() const;
        void set(double value);
    };
    
    struct string : public element {
        string(std::string const& value = "");
        string(pbd_conf conf, std::string const& value = "");
        std::string get() const;
        void set(std::string const& value);
    };
    
    struct boolean_array : public element {
        boolean_array();
        boolean_array(pbd_conf conf);
        int add(bool value);
        size_t size() const;
        std::vector<bool> values() const;
    };
    
    struct element_array : public element {
        element_array();
        element_array(pbd_conf conf);
        int add(element const& value);
        size_t size() const;
        std::vector<element> values() const;
    private:
        std::vector<element> elements;
    };
    
    struct integer_array : public element {
        integer_array();
        integer_array(pbd_conf conf);
        int add(int64_t value);
        size_t size() const;
        std::vector<int64_t> values() const;
    };
    
    struct real_array : public element {
        real_array();
        real_array(pbd_conf conf);
        int add(double value);
        size_t size() const;
        std::vector<double> values() const;
    };
    
}

#endif	/* PBDXX_H */

