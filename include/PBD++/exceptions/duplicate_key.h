#ifndef PBD_DUPLICATE_KEY_H_
#define PBD_DUPLICATE_KEY_H_

#include <boost/iostreams/detail/ios.hpp>
#include <string>

namespace PBD
{

class DuplicateKey : public BOOST_IOSTREAMS_FAILURE
{
public:
	DuplicateKey(std::string const& where, std::string const& key);
	virtual ~DuplicateKey() throw();
	
	std::string key() const;
	
private:
	std::string const key_;

	DuplicateKey& operator=(DuplicateKey const&);
};

}

#endif /*PBD_DUPLICATE_KEY_H_*/
