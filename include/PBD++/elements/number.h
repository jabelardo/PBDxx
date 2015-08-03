#ifndef PBDXX_NUMBER_H_
#define PBDXX_NUMBER_H_

#include <PBD++/details/streams_operators.h>
#include <PBD++/details/endianess.h>

namespace PBD
{
	
template<typename T_data>
class Number
{
public:
    typedef T_data DataType;
    typedef Number<T_data> NumberType;

    /**
    * Devuelve la data del elemento.
    * @return la data del elemento.
    */
    DataType value() const { return data_; }
	
protected:	    	
    Number(T_data d) : data_(d) {}

    ~Number() {}

    template<typename T>	
    void read(std::istream& is)
    {
        T datum;
        if (is >> Reader<T>(datum)) {
            data_ = datum;
        }
    }

    T_data data_;
};

}

#endif /*PBDXX_NUMBER_H_*/
