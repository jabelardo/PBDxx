#ifndef PBD_STRING_ELEMENT_MAP_H_
#define PBD_STRING_ELEMENT_MAP_H_

#if __cplusplus >= 201103L

#include <unordered_map>

namespace PBD
{
	class Element;
	typedef std::unordered_map<std::string, Element>  StringElementMap;
}

#elif __GNUC__ > 3

	#include <tr1/unordered_map>
	
	namespace PBD 
	{ 
		class Element;
		typedef std::tr1::unordered_map<std::string, Element>  StringElementMap;
	}
	
#else
	
	#include <map>

	namespace PBD 
	{ 
		class Element;
		typedef std::map<std::string, Element> StringElementMap;
	}

#endif // __GNUC__ > 3
	
#endif /*PBD_STRING_ELEMENT_MAP_H_*/
