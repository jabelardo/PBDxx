#ifndef PBDXX_NUMBER_ARRAY_H_
#define PBDXX_NUMBER_ARRAY_H_

#include <PBD++/details/streams_operators.h>
#include <PBD++/details/endianess.h>
#include <PBD++/elements/array.h>
#include <vector>

namespace PBD
{

template<typename T_data>
class NumberArray : public Array<std::vector<T_data>, T_data>
{
public:
    typedef Array<std::vector<T_data>, T_data> Super;
    typedef T_data DataType;
    typedef NumberArray<T_data> NumberArrayType;
    typedef std::vector<T_data> VectorType;
	
protected:	    	
    /**
     * @throws std::invalid_argument
     */
    NumberArray(VectorType const& d) : Super(d) {}

    NumberArray() {}

    ~NumberArray() {}

    std::pair<DataType, DataType> data_range() const
    {
        DataType min = 0;
        DataType max = 0;
        if (!Super::data_.empty()) {
            min = *std::min_element(Super::data_.begin(), Super::data_.end());
            max = *std::max_element(Super::data_.begin(), Super::data_.end());
        }
        return std::make_pair(min, max);
    }

    template<typename T>
    void read(std::istream& is)
    {    
        std::vector<T> vector;
        if (is >> VectorReader<T>(vector)) {
            Super::data_.assign(vector.begin(), vector.end());
        }
    }

    template <typename T>
    static T write_cast(DataType val)
    {
       return static_cast<T>(val);
    }

    template<typename T>
    void write(std::ostream& os) const
    {
        std::vector<T> vector;
        vector.reserve(Super::data_.size());
        std::transform(Super::data_.begin(), Super::data_.end(), std::back_inserter(vector), write_cast<T>);

        os << VectorWriter<T>(vector);
    }
};

}

#endif /*PBDXX_NUMBER_ARRAY_H_*/
