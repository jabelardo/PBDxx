#ifndef PBD_ELEMENT_IMPLEMENTATION_H_
#define PBD_ELEMENT_IMPLEMENTATION_H_

#include <PBD++/details/type_id.h>
#include <PBD++/streams.h>
#include <boost/noncopyable.hpp>
#include <PBD++/details/shared_ptr.h>

namespace PBD
{

class ElementMap;
class ElementArray;
class StringArray;
class BooleanArray;
class IntegerArray;
class RealArray;
class String;
class Boolean;
class Integer;
class Real;
class Null;

/**
 * Clase abstracta que define cada elemento de un mensaje pdb.
 */
class ElementImplementation : boost::noncopyable
{
protected:
	ElementImplementation();	
	
public:    
    static void destroy(ElementImplementation* e);
    
    virtual ~ElementImplementation() = 0;
    	
	/**
     * Devuelve el tipo del elemento.
     * @return un TypeId que identifica el tipo del elemento.
     */
    virtual TypeId::TypeId type_id() const = 0;

    /**
     * Metodo de conversion a Mapa de string (ElementMap).
     * @return una referencia a esta clase si es de tipo ElementMap
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual ElementMap& as_element_map();
    virtual ElementMap const& as_element_map() const;

    /**
     * Metodo de conversion a arreglo de elementos (ElementArray).
     * @return una referencia a esta clase si es de tipo ElementArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual ElementArray& as_element_array();
    virtual ElementArray const& as_element_array() const;

    /**
     * Metodo de conversion a arreglo de string (StringArray).
     * @return una referencia a esta clase si es de tipo StringArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual StringArray& as_string_array();
    virtual StringArray const& as_string_array() const;

    /**
     * Metodo de conversion a arreglo de enteros (IntegerArray).
     * @return una referencia a esta clase si es de tipo IntegerArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual IntegerArray& as_integer_array();
    virtual IntegerArray const& as_integer_array() const;

    /**
     * Metodo de conversion a arreglo de reales (RealArray).
     * @return una referencia a esta clase si es de tipo RealArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual RealArray& as_real_array();
    virtual RealArray const& as_real_array() const;

    /**
     * Metodo de conversion a arreglo de booleanos (BooleanArray).
     * @return una referencia a esta clase si es de tipo BooleanArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual BooleanArray& as_boolean_array();
    virtual BooleanArray const& as_boolean_array() const;

    /**
     * Metodo de conversion a elemento de String (String).
     * @return una referencia a esta clase si es de tipo String
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual String& as_string();
    virtual String const& as_string() const;

   /**
     * Metodo de conversion a elemento de Boolean (Boolean).
     * @return una referencia a esta clase si es de tipo Boolean
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual Boolean& as_boolean();
    virtual Boolean const& as_boolean() const;

   /**
     * Metodo de conversion a elemento de enteros (Integer).
     * @return una referencia a esta clase si es de tipo Integer
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual Integer& as_integer();
    virtual Integer const& as_integer() const;

   /**
     * Metodo de conversion a elemento de reales (Real).
     * @return una referencia a esta clase si es de tipo Real
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual Real& as_real();
    virtual Real const& as_real() const;

   /**
     * Metodo de conversion a elemento vacio (Null).
     * @return una referencia a esta clase si es de tipo Null
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    virtual Null& as_null();
    virtual Null const& as_null() const;    
    
	/**
     * Devuelve el "tipo fisico Real" del elemento al momento de escribirse.
     * @return un TypeId que identifica el tipo del elemento.
     */
	virtual TypeId::TypeId type_id_to_write() const = 0;
    /**
     * Metodo abstracto que difine la accion de leer de un stream de entrada.
     * @param is el stream de entrada de donde se leeran los datos.
     * @param type indica el "tipo fisico Real" de datos que contiene el stream de entrada.
     */
    virtual void read(std::istream& is, TypeId::TypeId type) = 0;    
    
    /**
     * Metodo abstracto que difine la accion de escribir a un stream de salida.
     * @param os el stream de salida a donde se escribira.
     * @param type indica el "tipo fisico Real" de datos que se escribirá al stream de salida.
     */
    virtual void write(std::ostream& os, TypeId::TypeId type) const = 0;
    
    typedef PBD::shared_ptr<ElementImplementation> SharedPtr;
    
    virtual SharedPtr clone() const = 0;
};

}

#endif /*ELEMENT_IMPLEMENTATION_H_*/
