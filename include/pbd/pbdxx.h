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
#include <stdexcept>
#include <pbd/pbd.h>

namespace pbdxx {

    struct boolean;
    struct boolean_array;
    struct element;
    struct element_array;
    struct integer;
    struct integer_array;
    struct null;
    struct real;
    struct real_array;
    struct string;
    
    struct bad_cast_exception : public std::runtime_error {
        bad_cast_exception(const std::string& what);
        virtual ~bad_cast_exception() throw();
    };
    
    struct element_base {
        
        static element_base* create(pbd_type_id type);
        
        static element_base* create(pbd_conf conf, pbd_type_id type);
        
        static element_base* create(pbd_conf conf, pbd_element* impl);
        
        static void destroy(element_base* e);
        
        virtual ~element_base() = 0;
        
        pbd_type_id type() const;   

        pbd_conf config() const;     
        
        int to_buffer(std::vector<char>& buffer);
        
        virtual const boolean& as_boolean() const;    
        virtual boolean& as_boolean();    
        
        virtual const boolean_array& as_boolean_array() const;  
        virtual boolean_array& as_boolean_array();   
        
        virtual const element_array& as_element_array() const;   
        virtual element_array& as_element_array(); 
        
        virtual const integer& as_integer() const;      
        virtual integer& as_integer();   
        
        virtual const integer_array& as_integer_array() const;   
        virtual integer_array& as_integer_array(); 
        
        virtual const real& as_real() const;  
        virtual real& as_real();  
        
        virtual const real_array& as_real_array() const;  
        virtual real_array& as_real_array();  
        
        virtual const string& as_string() const;  
        virtual string& as_string();
        
        protected:
            element_base(pbd_element* impl);
            element_base(pbd_conf conf, pbd_element* impl);
            pbd_conf conf;
            pbd_element* impl;
            friend struct element_array;
            
        private:
            element_base() = delete;
            element_base(const element_base& e) = delete; // non construction-copyable
            element_base& operator=(const element_base&) = delete; // non copyable
    };
    
    struct null : public element_base {
    protected:
        friend struct element;
        friend struct element_base;
        null();
        null(pbd_conf conf);
        null(pbd_conf conf, pbd_element* impl);
    };
    
    struct boolean : public element_base {
        bool get() const;
        void set(bool value);
        virtual const boolean& as_boolean() const;    
        virtual boolean& as_boolean();  
    protected:
        friend struct element_base;
        boolean(bool value = false);
        boolean(pbd_conf conf, bool value = false);
        boolean(pbd_conf conf, pbd_element* impl, bool value = false);
    };
    
    struct integer : public element_base {
        int64_t get() const;
        void set(int64_t value);
        virtual const integer& as_integer() const;      
        virtual integer& as_integer(); 
    protected:
        friend struct element_base;
        integer(int64_t value = 0);
        integer(pbd_conf conf, int64_t value = 0);
        integer(pbd_conf conf, pbd_element* impl, int64_t value = 0);
    };
    
    struct real : public element_base {
        double get() const;
        void set(double value);
        virtual const real& as_real() const;      
        virtual real& as_real(); 
    protected:
        friend struct element_base;
        real(double value = 0);
        real(pbd_conf conf, double value = 0);
        real(pbd_conf conf, pbd_element* impl, double value = 0);
    };
    
    struct string : public element_base {
        std::string get() const;
        void set(std::string const& value);
        virtual const string& as_string() const;      
        virtual string& as_string(); 
    protected:
        friend struct element_base;
        string(std::string const& value = "");
        string(pbd_conf conf, std::string const& value = "");
        string(pbd_conf conf, pbd_element* impl, std::string const& value = "");
    };
    
    struct boolean_array : public element_base {
        int add(bool value);
        size_t size() const;
        std::vector<bool> values() const;
        virtual const boolean_array& as_boolean_array() const;      
        virtual boolean_array& as_boolean_array(); 
    protected:
        friend struct element_base;
        boolean_array();
        boolean_array(pbd_conf conf);
        boolean_array(pbd_conf conf, pbd_element* impl);
    };
    
    struct element_array : public element_base {
        int add(element const& value);
        size_t size() const;
//        std::vector<element> values() const;
        virtual const element_array& as_element_array() const;      
        virtual element_array& as_element_array(); 
    protected:
        friend struct element_base;
        element_array();
        element_array(pbd_conf conf);
        element_array(pbd_conf conf, pbd_element* impl);
    //private:
        //std::vector<element> elements;
    };
    
    struct integer_array : public element_base {
        int add(int64_t value);
        size_t size() const;
        std::vector<int64_t> values() const;
        virtual const integer_array& as_integer_array() const;      
        virtual integer_array& as_integer_array(); 
    protected:
        friend struct element_base;
        integer_array();
        integer_array(pbd_conf conf);
        integer_array(pbd_conf conf, pbd_element* impl);
    };
    
    struct real_array : public element_base {
        int add(double value);
        size_t size() const;
        std::vector<double> values() const;
        virtual const real_array& as_real_array() const;      
        virtual real_array& as_real_array(); 
    protected:
        friend struct element_base;
        real_array();
        real_array(pbd_conf conf);
        real_array(pbd_conf conf, pbd_element* impl);
    };
    
    struct element {
        element(pbd_conf conf = pbd_default_conf);
        element(pbd_type_id type, pbd_conf conf = pbd_default_conf);
        element(const std::shared_ptr<element_base>& impl);
        
        static element from_buffer(std::vector<char> const& buffer, size_t& read_bytes, pbd_conf conf = pbd_default_conf);
        
        static element create_null(pbd_conf conf = pbd_default_conf);
        static element create_boolean(bool value = false, pbd_conf conf = pbd_default_conf);
        static element create_integer(int64_t value = 0, pbd_conf conf = pbd_default_conf);
        static element create_real(double value = 0, pbd_conf conf = pbd_default_conf);
        static element create_string(const std::string& value = "", pbd_conf conf = pbd_default_conf);
        static element create_boolean_array(pbd_conf conf = pbd_default_conf);
        static element create_integer_array(pbd_conf conf = pbd_default_conf);
        static element create_real_array(pbd_conf conf = pbd_default_conf);
        static element create_element_array(pbd_conf conf = pbd_default_conf);
        
        int to_buffer(std::vector<char>& buffer);
        
        pbd_type_id type() const;           
        
        const boolean& as_boolean() const;    
        boolean& as_boolean();    
        
        const boolean_array& as_boolean_array() const;  
        boolean_array& as_boolean_array();   
        
        const element_array& as_element_array() const;   
        element_array& as_element_array(); 
        
        const integer& as_integer() const;      
        integer& as_integer();   
        
        const integer_array& as_integer_array() const;   
        integer_array& as_integer_array(); 
        
        const real& as_real() const;  
        real& as_real();  
        
        const real_array& as_real_array() const;  
        real_array& as_real_array();  
        
        const string& as_string() const;  
        string& as_string();
        
    protected:
        std::shared_ptr<element_base> impl; 
        friend struct element_array;
    };
}

#endif	/* PBDXX_H */

