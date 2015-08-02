#ifndef PBD_TYPE_ID_H_
#define PBD_TYPE_ID_H_

#include <cstdlib>
#include <PBD++/details/cstdint.h>

namespace PBD
{

namespace TypeId
{
/**
 * Constantes que definen el identificador de los tipos definidos por el
 * protocolo.
 */
enum TypeId
{
        unknown	      =   0
    /**
     * IMPORTANTE: es necesario que se respete la distancia entre 
     * los _scalar y los _array usando el valor scalar_delta. Vea la 
     * implementacion de select_best_integer y select_best_real para mas 
     * detalles
     */
    ,   int8_scalar   =   1
    ,   uint8_scalar  =   4
    ,   int16_scalar  =   7
    ,   uint16_scalar =  10
    ,   int32_scalar  =  13
    ,   uint32_scalar =  16
    ,   int64_scalar  =  19
    ,   float_scalar  =  22
    ,   double_scalar =  25
        
    ,   scalar_delta  =  40
    ,   int8_array    =  41
    ,   uint8_array   =  44
    ,   int16_array   =  47
    ,   uint16_array  =  50
    ,   int32_array   =  53
    ,   uint32_array  =  56
    ,   int64_array   =  59
    ,   float_array   =  62
    ,   double_array  =  65

    ,   real          =  80
    ,   integer       =  81
    ,   boolean       =  82
    ,   null          =  83
    
    ,   string        =  84
    ,   integer_array =  87
    ,   real_array    =  90
    ,   boolean_array =  93
    ,   string_array  =  96
    ,   element_array =  99
    ,   element_map   = 102
    
    ,   int8_array_one_byte       = int8_array
    ,   int8_array_two_bytes
    ,   int8_array_three_bytes
    
    ,   uint8_array_one_byte      = uint8_array
    ,   uint8_array_two_bytes
    ,   uint8_array_three_bytes
    
    ,   int16_array_one_byte      = int16_array
    ,   int16_array_two_bytes
    ,   int16_array_three_bytes
    
    ,   uint16_array_one_byte     = uint16_array
    ,   uint16_array_two_bytes
    ,   uint16_array_three_bytes
    
    ,   int32_array_one_byte      = int32_array
    ,   int32_array_two_bytes
    ,   int32_array_three_bytes
    
    ,   uint32_array_one_byte     = uint32_array
    ,   uint32_array_two_bytes
    ,   uint32_array_three_bytes
    
    ,   int64_array_one_byte      = int64_array
    ,   int64_array_two_bytes
    ,   int64_array_three_bytes
    
    ,   float_array_one_byte      = float_array
    ,   float_array_two_bytes
    ,   float_array_three_bytes
    
    ,   double_array_one_byte     = double_array
    ,   double_array_two_bytes
    ,   double_array_three_bytes
    
    ,   boolean_array_one_byte    = boolean_array
    ,   boolean_array_two_bytes
    ,   boolean_array_three_bytes
    
    ,   string_array_one_byte     = string_array
    ,   string_array_two_bytes
    ,   string_array_three_bytes
    
    ,   element_array_one_byte    = element_array
    ,   element_array_two_bytes
    ,   element_array_three_bytes
    
    ,   element_map_one_byte      = element_map
    ,   element_map_two_bytes
    ,   element_map_three_bytes
    
    ,   string_one_byte           = string
    ,   string_two_bytes
    ,   string_three_bytes
};

TypeId to_write(TypeId type, std::size_t size);

TypeId from_read(TypeId type);

TypeId  best_integer(int64_t val);

TypeId  best_integer_array(int64_t min, int64_t max);

TypeId  best_real(double val);

TypeId  best_real_array(double min, double max);

} // namespace TypeId

} // namespace PBD

#endif /*PBD_TYPE_ID_H_*/
