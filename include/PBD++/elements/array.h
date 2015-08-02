#ifndef PBD_ARRAY_H_
#define PBD_ARRAY_H_

namespace PBD
{

template<typename T_data, typename T_datum>
struct ArrayValidator
{
	ArrayValidator() {}

	ArrayValidator(T_data const&) {}

	void operator() (T_datum const&) {}
};

template<typename T_data, typename T_datum>
class Array
{
	typedef ArrayValidator<T_data, T_datum> Validator;
public:    
    T_data const& value() const 
    { 
        return data_; 
    }
    
    /**
 	 * @throws std::invalid_argument
 	 */
    void  push_back(T_datum const& datum)
    {
    	validator_(datum);
        data_.push_back(datum);
    }
    
    std::size_t size() const
    {
        return data_.size(); 
    }
    
    T_datum const& at(std::size_t idx) const
    {
        return data_.at(idx); 
    }
    
    T_datum const& operator[](std::size_t idx) const
    {
        return data_[idx]; 
    }    

protected:
    Array() {}
    
    Array(T_data const& data)
		: validator_(data), data_(data)
	{
	}
    
    ~Array() {}
    
    Validator validator_;
    T_data data_;
};

}

#endif /*PBD_ARRAY_H_*/
