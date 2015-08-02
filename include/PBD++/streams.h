#ifndef PBD_STREAMS_H_
#define PBD_STREAMS_H_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4702) // unreachable code
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#pragma warning(pop)
#else
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#endif


#include <vector>
#include <PBD++/details/endianess.h>

namespace PBD
{

//-----------------------------------------------------------------------------

class FilterOutStream : public boost::iostreams::filtering_ostream 
{	
public:
	FilterOutStream(std::vector<char>& buffer);
};	

//-----------------------------------------------------------------------------

class FilterInStream : public boost::iostreams::filtering_istream  
{
public:    
	FilterInStream(std::vector<char> const& buffer);
	
	void endianess(Endianess::Endianess endianess);
	Endianess::Endianess endianess() const;
	
private:
    Endianess::Endianess endianess_;
};

//-----------------------------------------------------------------------------

class VectorCharSink : public boost::iostreams::sink
{
public:
	VectorCharSink(std::vector<char>& buffer);

    std::streamsize write(const char* s, std::streamsize n);

private:
    std::vector<char>& buffer_;

	VectorCharSink& operator=(VectorCharSink const&);
};

//-----------------------------------------------------------------------------

class VectorCharSource : public boost::iostreams::source
{
public:
	VectorCharSource(std::vector<char>& buffer);
    
    std::streamsize read(char* s, std::streamsize n);
    
private:
    std::vector<char>& buffer_;

	VectorCharSource& operator=(VectorCharSource const&);
};

//-----------------------------------------------------------------------------

typedef boost::iostreams::stream<VectorCharSink> OutVectorCharStream;

typedef boost::iostreams::stream<VectorCharSource> InVectorCharStream;

}

#endif /*PBD_STREAMS_H_*/
