#include <PBD++/details/type_id.h>
#include <PBD++/details/cstdint.h>
#include <limits>

namespace PBD
{

namespace TypeId
{

TypeId
from_read(TypeId type)
{
    switch (type) {
        case int8_array_one_byte:
        case int8_array_two_bytes:
        case int8_array_three_bytes:
            return int8_array;

        case uint8_array_one_byte:
        case uint8_array_two_bytes:
        case uint8_array_three_bytes:
            return uint8_array;

        case int16_array_one_byte:
        case int16_array_two_bytes:
        case int16_array_three_bytes:
            return int16_array;

        case uint16_array_one_byte:
        case uint16_array_two_bytes:
        case uint16_array_three_bytes:
            return uint16_array;

        case int32_array_one_byte:
        case int32_array_two_bytes:
        case int32_array_three_bytes:
            return int32_array;

        case uint32_array_one_byte:
        case uint32_array_two_bytes:
        case uint32_array_three_bytes:
            return uint32_array;

        case int64_array_one_byte:
        case int64_array_two_bytes:
        case int64_array_three_bytes:
            return int64_array;

        case float_array_one_byte:
        case float_array_two_bytes:
        case float_array_three_bytes:
            return float_array;

        case double_array_one_byte:
        case double_array_two_bytes:
        case double_array_three_bytes:
            return double_array;

        case boolean_array_one_byte:
        case boolean_array_two_bytes:
        case boolean_array_three_bytes:
            return boolean_array;

        case string_array_one_byte:
        case string_array_two_bytes:
        case string_array_three_bytes:
            return string_array;

        case element_array_one_byte:
        case element_array_two_bytes:
        case element_array_three_bytes:
            return element_array;

        case element_map_one_byte:
        case element_map_two_bytes:
        case element_map_three_bytes:
            return element_map;

        case string_one_byte:
        case string_two_bytes:
        case string_three_bytes:
            return string;

		default:
			return type;
	}
}

TypeId  
best_integer_array(int64_t min, int64_t max)
{
    if (min >= 0) { // unsigned
        if (max <= std::numeric_limits<uint8_t>::max())
            return uint8_array;
        if (max <= std::numeric_limits<uint16_t>::max())
            return uint16_array;
        if (max <= std::numeric_limits<uint32_t>::max())
            return uint32_array;
    } else { // signed
        if (min >= std::numeric_limits<int8_t>::min()) {
            if (max <= std::numeric_limits<int8_t>::max())
                return int8_array;
            if (max <= std::numeric_limits<int16_t>::max())
                return int16_array;
            if (max <= std::numeric_limits<int32_t>::max())
                return int32_array;
        } else if (min >= std::numeric_limits<int16_t>::min()) {
            if (max <= std::numeric_limits<int16_t>::max())
                return int16_array;
            if (max <= std::numeric_limits<int32_t>::max())
                return int32_array;
        } else if (min >= std::numeric_limits<int32_t>::min()) {
            if (max <= std::numeric_limits<int32_t>::max())
                return int32_array;
        }
    }
    return int64_array;
}

TypeId 
best_integer(int64_t val)
{
    return TypeId(best_integer_array(val, val) - scalar_delta);
}

TypeId 
to_write(TypeId type, std::size_t size)
{
    switch (type) {    	
		case int8_array:
		case uint8_array:
		case int16_array:
		case uint16_array:
		case int32_array:
		case uint32_array:
		case int64_array:
		case float_array:
		case double_array:
		case boolean_array:
		case string_array:    
		case element_array:
		case element_map:
		case string:
		    if (size > 65535)
		        return TypeId(type + 2);
		    else if (size > 255)
		        return TypeId(type + 1);
	            
		default: break;		        
	}
	return type;
}

TypeId  
best_real(double val)
{
    return TypeId(best_real_array(val, val) - scalar_delta);
}

TypeId  
best_real_array(double min, double max)
{
    if (min >= std::numeric_limits<float>::min()
        && max <= std::numeric_limits<float>::max()) {
            return float_array;
    }
    return double_array;
}

} // namespace TypeId

} //namespace PBD
