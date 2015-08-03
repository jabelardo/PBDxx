#define PBD_UNIT_TEST_
#include <PBD++/pbdoc.h>
#include <PBD++/elements.h>
#include <boost/crc.hpp>
#include <boost/detail/endian.hpp>
#include <PBD++/elements/integer.h>
#include <PBD++/streams.h>

#include <sstream>
#include <strstream>
#include <iostream>

#include <boost/test/unit_test.hpp>

using namespace PBD;

BOOST_AUTO_TEST_CASE(test_message_writer)
{
    uint8_t const integer_value = 4;

    Element body_data(Element::create_integer(integer_value));

    PbDocWriter pbdoc_writer(body_data);

    std::vector<char> buffer;
    OutVectorCharStream out(buffer);
    pbdoc_writer.write(out);
    out.flush();

#ifdef BOOST_LITTLE_ENDIAN
    BOOST_CHECK_EQUAL((PbDocHeadFlags::Flags(buffer[0]) & PbDocHeadFlags::ENDIAN_MASK), PbDocHeadFlags::LITTLE_ENDIAN_FLAG);
    BOOST_CHECK_NE   ((PbDocHeadFlags::Flags(buffer[0]) & PbDocHeadFlags::ENDIAN_MASK), PbDocHeadFlags::BIG_ENDIAN_FLAG);
#else
    BOOST_CHECK_NE   ((PbDocHeadFlags::Flags(buffer[0]) & PbDocHeadFlags::ENDIAN_MASK), PbDocHeadFlags::LITTLE_ENDIAN_FLAG);
    BOOST_CHECK_EQUAL((PbDocHeadFlags::Flags(buffer[0]) & PbDocHeadFlags::ENDIAN_MASK), PbDocHeadFlags::BIG_ENDIAN_FLAG);
#endif
    BOOST_CHECK_EQUAL((PbDocHeadFlags::Flags(buffer[0]) & PbDocHeadFlags::VERSION_MASK), PbDocHeadFlags::VERSION);

    BOOST_CHECK_EQUAL(pbdoc_writer.head_.version(), 1);

    InVectorCharStream iss(buffer);
    
    PbDocReader pbdoc_reader;
    size_t size = 0;
    BOOST_CHECK_EQUAL(pbdoc_reader.buffer_.size(), size);

    pbdoc_reader.read_head(iss);
    size += pbdoc_reader.head_size();
    BOOST_CHECK_EQUAL(pbdoc_reader.buffer_.size(), size);

    BOOST_CHECK_EQUAL(pbdoc_reader.buffer_.size(), size);
    BOOST_CHECK_EQUAL(pbdoc_reader.body_size(), 2U);

    pbdoc_reader.read_body(iss);
    size += pbdoc_reader.body_size();

    BOOST_CHECK_EQUAL(integer_value, (uint8_t)(pbdoc_reader.buffer_[pbdoc_reader.buffer_.size()-1]));

    BOOST_CHECK_EQUAL(pbdoc_reader.buffer_.size(), size);

    pbdoc_reader.read_checksum(iss);

    PbDoc pbdoc = pbdoc_reader.create_pbdoc();
    Element element = pbdoc.get_body();
    Integer& integer = element.as_integer();
    BOOST_CHECK_EQUAL(integer.value(), integer_value);
}
