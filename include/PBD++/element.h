#ifndef PBDXX_ELEMENT_H_
#define PBDXX_ELEMENT_H_

#include <iosfwd>
#include <string>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <PBD++/details/type_id.h>
#include <PBD++/details/shared_ptr.h>
#include <PBD++/details/string_element_map.h>

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
class ElementImplementation;

/**
 * Clase que define cada elemento de un mensaje pdb bajo un patron de diseño handler.
 * Esta clase delega en ElementImplementation toda la implementación. Esta clase
 * utiliza el mecanismo de copy on write para el manejo del shared pointer a
 * ElementImplementation. Dicha conducta esta encapsulada en el par de métodos
 * implementation() y implementation() const
 */
class Element
{
public:
    typedef shared_ptr<ElementImplementation> ImplSharedPtr;
    
    Element();
    Element(ImplSharedPtr const& impl);
    explicit Element(ElementImplementation const& impl);
    Element(Element const& e);
    Element& operator=(Element const& e);
    
    static Element create_string(std::string const& datum = "");

    static Element create_boolean(bool datum = false);

    static Element create_null();
    
    static Element create_integer(int64_t datum = 0);
    
    static Element create_real(double datum = 0);
    
    static Element create_string_array();
    static Element create_string_array(std::vector<std::string> const& vector_to_copy);
    
    static Element create_boolean_array();
    static Element create_boolean_array(boost::dynamic_bitset<> const& set_to_copy);
    
    static Element create_integer_array();
    static Element create_integer_array(std::vector<int64_t> const& vector_to_copy);
    
    static Element create_real_array();
    static Element create_real_array(std::vector<double> const& vector_to_copy);
    
    static Element create_element_array();
    static Element create_element_array(std::vector<Element> const& vector_to_copy);
    
    static Element create_element_map(StringElementMap const& map_to_copy);
    static Element create_element_map();
    /**
     * Crea un nuevo ElementImplementation vacio a partir del tipo que va a contener.
     * @param type define el tipo del cual se creara el elemento.
     * @throws PBD::InvalidTypeId en caso que el tipo no sea valido
     */     
    static Element create(TypeId::TypeId type);
    
    ~Element();
	
	/**
     * Devuelve el tipo del elemento.
     * @return un TypeId que identifica el tipo del elemento.
     */
    TypeId::TypeId type_id() const;

    /**
     * Metodo de conversion a mapa de elementos (ElementMap).
     * @return una referencia a esta clase si es de tipo ElementMap
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    ElementMap& as_element_map();
    ElementMap const& as_element_map() const;

    /**
     * Metodo de conversion a arreglo de elementos (ElementArray).
     * @return una referencia a esta clase si es de tipo ElementArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    ElementArray& as_element_array();
    ElementArray const& as_element_array() const;

    /**
     * Metodo de conversion a arreglo de string (StringArray).
     * @return una referencia a esta clase si es de tipo StringArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    StringArray& as_string_array();
    StringArray const& as_string_array() const;

    /**
     * Metodo de conversion a arreglo de enteros (IntegerArray).
     * @return una referencia a esta clase si es de tipo IntegerArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    IntegerArray& as_integer_array();
    IntegerArray const& as_integer_array() const;

    /**
     * Metodo de conversion a arreglo de reales (RealArray).
     * @return una referencia a esta clase si es de tipo RealArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    RealArray& as_real_array();
    RealArray const& as_real_array() const;

    /**
     * Metodo de conversion a arreglo de booleanos (BooleanArray).
     * @return una referencia a esta clase si es de tipo BooleanArray
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    BooleanArray& as_boolean_array();
    BooleanArray const& as_boolean_array() const;

    /**
     * Metodo de conversion a elemento de string (String).
     * @return una referencia a esta clase si es de tipo String
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    String& as_string();
    String const& as_string() const;

   /**
     * Metodo de conversion a elemento de Boolean (Boolean).
     * @return una referencia a esta clase si es de tipo Boolean
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    Boolean& as_boolean();
    Boolean const& as_boolean() const;

   /**
     * Metodo de conversion a elemento de enteros (Integer).
     * @return una referencia a esta clase si es de tipo Integer
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    Integer& as_integer();
    Integer const& as_integer() const;

   /**
     * Metodo de conversion a elemento de reales (Real).
     * @return una referencia a esta clase si es de tipo Real
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    Real& as_real();
    Real const& as_real() const;

   /**
     * Metodo de conversion a elemento vacio (Null).
     * @return una referencia a esta clase si es de tipo Null
     * @throws PBD::BadCast en caso de no ser valida la conversion.
     */
    Null& as_null();
    Null const& as_null() const; 
    
    /**
     * Devuelve el "tipo fisico Real" del elemento al momento de escribirse.
     * @return un TypeId que identifica el tipo del elemento.
     */
    TypeId::TypeId type_id_to_write() const;
    
    /**
     * Metodo que difine la accion de leer de un stream de entrada.
     * @param is el stream de entrada de donde se leeran los datos.
     * @param type indica el "tipo fisico Real" de datos que contiene el stream de entrada.
     */
    void read(std::istream& is, TypeId::TypeId type);    
    
    /**
     * Metodo que difine la accion de escribir a un stream de salida.
     * @param os el stream de salida a donde se escribira.
     * @param type indica el "tipo fisico Real" de datos que se escribirá al stream de salida.
     */
    void write(std::ostream& os, TypeId::TypeId type) const;
    
    /**
     * metodo para hacer una copia profunda del contenido del elemento. la copia normal
     * (por asignación) es una copia superficial que lo que hace es incrementar en uno
     * la referencia
     */
    Element clone() const;
    
    /**
     * intercambia el contenido de dos elementos
     */
    void swap(Element& e);

#ifndef PBD_UNIT_TEST_
    private:    
#else
    public:
#endif /*PBD_UNIT_TEST_*/

    ImplSharedPtr implementation() const;
    ImplSharedPtr implementation();    
    
    ImplSharedPtr implementation_;
    bool is_a_copy_;
            
};

std::ostream& operator<<(std::ostream& os, Element const& e);
std::istream& operator>>(std::istream& is, Element& e);

}

#endif /*PBDXX_ELEMENT_H_*/
