#ifndef PBD_INVALID_TYPE_ID_H_
#define PBD_INVALID_TYPE_ID_H_

#include <boost/iostreams/detail/ios.hpp>
#include <PBD++/details/type_id.h>
#include <string>

namespace PBD
{

class InvalidTypeId : public BOOST_IOSTREAMS_FAILURE
{
public:
	InvalidTypeId(std::string const& where, TypeId::TypeId tid);
	virtual ~InvalidTypeId() throw();
	
	TypeId::TypeId type_id() const;
	
private:
	TypeId::TypeId const TypeId_;

	InvalidTypeId& operator=(InvalidTypeId const&);
};

}

#endif /*PBD_INVALID_TYPE_ID_H_*/
