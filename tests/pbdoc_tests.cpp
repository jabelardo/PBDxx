#define PBD_UNIT_TEST_
#include <PBD++/pbdoc.h>
#include <PBD++/elements.h>
#include <boost/crc.hpp>
#include <boost/detail/endian.hpp>
#include <PBD++/elements/integer.h>
#include <PBD++/streams.h>

//#include <PBD-RPC++/response.h>

#include <sstream>
#include <strstream>
#include <iostream>

#include <boost/test/unit_test.hpp>

using namespace PBD;
//using namespace PBD_RPC;

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

//BOOST_AUTO_TEST_CASE(test_message_writer_2)
//{
//    boost::int64_t ticket_preventa_id = 1;
//    boost::int64_t primer_indice_taquilla = 1;
//    boost::int64_t ultimo_indice_taquilla = 1200;
//    double montoDado = 5;
//    std::vector<boost::int64_t> excepApuestaId;
//    std::vector<double> excepMontoDado;
//
//    for (int i = 0; i < 256; ++i) {
//        excepApuestaId.push_back(i);
//        excepMontoDado.push_back(i);
//    }
//
//    PBD::ElementArray result;
//    result.push_back(PBD::Integer(ticket_preventa_id));
//    result.push_back(PBD::Integer(primer_indice_taquilla));
//    result.push_back(PBD::Integer(ultimo_indice_taquilla));
//    result.push_back(PBD::Real(montoDado));
//    result.push_back(PBD::IntegerArray(excepApuestaId));
//    //result.push_back(PBD::RealArray(excepMontoDado));
//
//    std::string getMethod = "getMethod";
//    boost::int64_t getId = 1;
//
//    PBD_RPC::Response response(getMethod, result.clone(), getId);
//
//    std::vector<char> buffer;
//    PBD::OutVectorCharStream out(buffer);
//
//    response.copyTo(out);
//    out.flush();
//
//    InVectorCharStream iss(buffer);
//    PbDocReader reader;
//    reader.one_step_read(iss);
//
//    PBD::PbDoc pbdoc = reader.create_pbdoc();
//    PBD::Element element = pbdoc.get_body();
//
//    PBD_RPC::Message message(element.as_element_array());
//
////                switch (message.getType()) {                    case PBD_RPC::Message::ResponseType: {
//
//    PBD_RPC::Response response2(message);
//}

//#if 1
//BOOST_AUTO_TEST_CASE(test_Message_type)
//{
//    uint8_t const serial = 1;
//    uint16_t const connectionId = 2;
//    uint16_t const body_type = 3;
//
//    Message messagesrc(serial, connectionId);
//    IntegerArray array_;
//
//    uint8_t const max = std::numeric_limits<uint8_t>::max() ;
//
//    for (int var = 0; var < 256; ++var) {
//		array_.push_back(max - uint8_t(var));
//	}
//
//    Element bodyData;
//    BOOST_CHECK_EQUAL(array_.clone(bodyData));
//
//
//    {
//        std::vector<ACE_CDR::LongLong> cVector01;
//        BOOST_CHECK_EQUAL(array_.copyTo(cVector01));
//        BOOST_CHECK_EQUAL(cVector01.size() == 256U);
//
//       // std::cout << "cVector01.size() = "  << cVector01.size() << std::endl;
//
//        int valor = 0;
//
//        //std::cout << "*pos = ";
//        for (std::vector<ACE_CDR::LongLong>::const_iterator pos = cVector01.begin();
//             pos != cVector01.end(); ++pos)
//        {
//            uint8_t numero = uint8_t(max - valor);
//            BOOST_CHECK_EQUAL((uint8_t)(*pos) == numero);
//            valor++;
//            //std::cout << *pos << " " ;
//        }
//        //std::cout << std::endl;
//    }
//
//    //IntegerArray const *const integerArray_ = bodyData->asIntegerArray();
//    //std::cout << "--XXX-- integerArray_->typeId() = "  << integerArray_->typeId() << std::endl;
//
//    Body get_body(body_type, bodyData);
//    BOOST_CHECK_EQUAL(messagesrc.setBody(get_body));
//
//    PbDocWriter pbdoc_writer(messagesrc);
//    ACE_Message_Block* outputMsg;
//    BOOST_CHECK_EQUAL(pbdoc_writer.write(outputMsg));
//
//    uint8_t const* buffer = (uint8_t const*)outputMsg->rd_ptr();
//
//    BOOST_CHECK_EQUAL((buffer[0] & Head::BODY_SIZE_MASK) == TWO_BYTES_BODY_SIZE_BIT);
//
////    {
////        printf("                           ");
////        for (std::size_t i = 0; i < 267; ++i)
////            printf("%02X ", buffer[i]);
////        printf("\n");
////    }
//
//    ACE_Message_Block* msg = outputMsg->duplicate();
//    msg->wr_ptr(msg->rd_ptr());
//
//    PbDocReader pbdoc_reader;
//    BOOST_CHECK_EQUAL(pbdoc_reader.getHeadLength() == 4U);
//    msg->wr_ptr(pbdoc_reader.getHeadLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readHead(msg));
//    BOOST_CHECK_EQUAL(pbdoc_reader.getBodySizeLength() == 2U);
//    msg->wr_ptr(pbdoc_reader.getBodySizeLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readBodySize(msg));
//    BOOST_CHECK_EQUAL(pbdoc_reader.getBodyLength() == 261U);
//    msg->wr_ptr(pbdoc_reader.getBodyLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readBody(msg));
//    msg->wr_ptr(pbdoc_reader.getChecksumLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readChecksum(msg));
//
//    Message message;
//    BOOST_CHECK_EQUAL(pbdoc_reader.createMessage(msg, message));
//
//    msg->release();
//
//    BOOST_CHECK_EQUAL(message->getSerial() == serial);
//    BOOST_CHECK_EQUAL(message->getConnectionId() == connectionId);
//    BOOST_CHECK_EQUAL(message->getBodyType() == body_type);
//
//
//    Container const *const container = message->getBodyData();
//    BOOST_CHECK_EQUAL(container);
//    BOOST_CHECK_EQUAL(container->typeId()  == INTEGER_ARRAY_ID);
//    //std::cout << "container->typeId() = "  << container->typeId() << std::endl;
////
////    ACE_OutputCDR outContainer;
////    container->write(outContainer);
////    ACE_InputCDR inContainer(outContainer);
////    Element containerInt;
////    BOOST_CHECK_EQUAL(Container::create(inContainer, containerInt));
////
////
////   IntegerArray *const integerArray = containerInt->asIntegerArray();
////   BOOST_CHECK_EQUAL(integerArray);
//
//    IntegerArray const *const integerArray = message->getBodyData()->asIntegerArray();
//    BOOST_CHECK_EQUAL(integerArray);
//
//
//
///*
//    BOOST_CHECK_EQUAL(integerArray->typeId()  == INTEGER_ARRAY_ID);
//
//    std::vector<ACE_CDR::LongLong> cVector01;
//    BOOST_CHECK_EQUAL(integerArray->copyTo(cVector01));
//    BOOST_CHECK_EQUAL(cVector01.size() == 256U);
//
//    std::cout << "cVector01.size() = "  << cVector01.size() << std::endl;
//
//    int valor = 0;
//
//    for (std::vector<ACE_CDR::LongLong>::const_iterator pos = cVector01.begin();
//         pos != cVector01.end(); ++pos)
//    {
//        uint8_t numero = uint8_t(max - valor);
//        BOOST_CHECK_EQUAL((uint8_t)(*pos) == numero);
//        valor++;
//        std::cout << "*pos = "  << *pos << std::endl;
//    }
//*/
//
//}
//#endif
//
//#if 1
//BOOST_AUTO_TEST_CASE(test_Message_type2)
//{
//    uint8_t const serial = 1;
//    uint16_t const connectionId = 2;
//    uint16_t const body_type = 3;
//    ACE_CDR::ULong const bodySizeLength = 3;
//    ACE_CDR::ULong const headLength = 4;
//    std::size_t nDatos = 100000;
//
//    Message messagesrc(serial, connectionId);
//    IntegerArray array_;
//
//    uint8_t const max = std::numeric_limits<uint8_t>::max() ;
//
//    for (int var = 0; var < int(nDatos); ++var) {
//        array_.push_back(max - uint8_t(var));
//    }
//
//    Element bodyData;
//    BOOST_CHECK_EQUAL(array_.clone(bodyData));
//
//    Body get_body(body_type, bodyData);
//    BOOST_CHECK_EQUAL(messagesrc.setBody(get_body));
//
//    PbDocWriter pbdoc_writer(messagesrc);
//    ACE_Message_Block* outputMsg;
//    BOOST_CHECK_EQUAL(pbdoc_writer.write(outputMsg));
//
//    uint8_t const* buffer = (uint8_t const*)outputMsg->rd_ptr();
//
//    BOOST_CHECK_EQUAL((buffer[0] & Head::BODY_SIZE_MASK) == THREE_BYTES_BODY_SIZE_BIT);
//
////    ACE_Message_Block* msg = new ACE_Message_Block(os.total_length());
////
////    {
////       ACE_Message_Block const* out_msg = os.begin();
////       int count = 0;
////       do {
////           msg->copy(out_msg->rd_ptr(), out_msg->length());
////
////           std::cout << "test msg->length() = "  << msg->length()
////                     << " test out_msg.length() = " << out_msg->length() << std::endl;
////
////           printf("%i - ", count++);
////            for (int var = 0; var < 20; ++var) {
////                printf("%02X ", uint8_t(out_msg->rd_ptr()[var]));
////            }
////            printf("\n");
////
////       } while ((out_msg = out_msg->cont()));
////    }
//
//
//    ACE_Message_Block* msg = outputMsg->duplicate();
//    msg->wr_ptr(msg->rd_ptr());
//
//    PbDocReader pbdoc_reader;
//
//    BOOST_CHECK_EQUAL(pbdoc_reader.getHeadLength() == headLength);
//    msg->wr_ptr(pbdoc_reader.getHeadLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readHead(msg));
//
//    BOOST_CHECK_EQUAL(pbdoc_reader.getBodySizeLength() == bodySizeLength);
//
//    msg->wr_ptr(pbdoc_reader.getBodySizeLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readBodySize(msg));
//
//    BOOST_CHECK_EQUAL(pbdoc_reader.getBodyLength() == ACE_CDR::ULong(1+3+nDatos+2)); // el 3 es porke almacena 3 bytes para el size del contenedor
//
//    msg->wr_ptr(pbdoc_reader.getBodyLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readBody(msg));
//
//    msg->wr_ptr(pbdoc_reader.getChecksumLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readChecksum(msg));
//
//    Message messageout;
//
//    pbdoc_reader.createMessage( msg, messageout);
//
//    BOOST_CHECK_EQUAL(messageout->getBodyType() == body_type);
//    BOOST_CHECK_EQUAL(messageout->getSerial() == serial);
//    BOOST_CHECK_EQUAL(messageout->getConnectionId() == connectionId);
//
//
//    IntegerArray const *const integerArray = messageout->getBodyData()->asIntegerArray();
//    BOOST_CHECK_EQUAL(integerArray);
//
//    std::vector<ACE_CDR::LongLong> cVector01;
//    BOOST_CHECK_EQUAL(integerArray->copyTo(cVector01));
//    BOOST_CHECK_EQUAL(cVector01.size() == nDatos);
//
//    std::size_t pos = 0;
//    for (int var = 0; var < int(nDatos); ++var) {
//        uint8_t const numero = max - uint8_t(var);
//        BOOST_CHECK_EQUAL((uint8_t)(cVector01[pos++]) == numero);
//         if (pos > 506) break;
//    }
//
//
//
//    msg->release();
//    outputMsg->release();
//}
//#endif
//
//#if 1
//BOOST_AUTO_TEST_CASE(test_Message_prueba_boolean)
//{
//    uint8_t const serial = 1;
//    uint16_t const connectionId = 2;
//    uint16_t const body_type = 3;
//
//    Message messagesrc(serial, connectionId);
//    BooleanArray array_;
//
//    //uint8_t const max = std::numeric_limits<uint8_t>::max() ;
//
//    for (int var = 0; var < 100000; ++var) {
//        array_.push_back(true);
//    }
//
//    Element bodyData;
//    BOOST_CHECK_EQUAL(array_.clone(bodyData));
//    Body get_body(body_type, bodyData);
//    BOOST_CHECK_EQUAL(messagesrc.setBody(get_body));
//
//    PbDocWriter pbdoc_writer(messagesrc);
//    ACE_Message_Block* outputMsg;
//    BOOST_CHECK_EQUAL(pbdoc_writer.write(outputMsg));
//
//    uint8_t const* buffer = (uint8_t const*)outputMsg->rd_ptr();
//
//    BOOST_CHECK_EQUAL((buffer[0] & Head::BODY_SIZE_MASK) ==TWO_BYTES_BODY_SIZE_BIT);
//
//    ACE_Message_Block* msg = outputMsg->duplicate();
//    msg->wr_ptr(msg->rd_ptr());
//
//    PbDocReader pbdoc_reader;
//
//    BOOST_CHECK_EQUAL(pbdoc_reader.getHeadLength() == 4U);
//    msg->wr_ptr(pbdoc_reader.getHeadLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readHead(msg));
//
//    BOOST_CHECK_EQUAL(pbdoc_reader.getBodySizeLength() == 2U);
//
//    msg->wr_ptr(pbdoc_reader.getBodySizeLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readBodySize(msg));
//
//    BOOST_CHECK_EQUAL(pbdoc_reader.getBodyLength() == 12505U);
//
//    msg->wr_ptr(pbdoc_reader.getBodyLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readBody(msg));
//
//    msg->wr_ptr(pbdoc_reader.getChecksumLength());
//    BOOST_CHECK_EQUAL(pbdoc_reader.readChecksum(msg));
//
//    Message message;
//    BOOST_CHECK_EQUAL(pbdoc_reader.createMessage(msg, message));
//
//
//    BOOST_CHECK_EQUAL(message->getSerial() == serial);
//    BOOST_CHECK_EQUAL(message->getConnectionId() == connectionId);
//    BOOST_CHECK_EQUAL(message->getBodyType() == body_type);
//
//
//    Container const *const container = message->getBodyData();
//    BOOST_CHECK_EQUAL(container);
//    BOOST_CHECK_EQUAL(container->typeId()  == BOOLEAN_ARRAY_ID);
//
//    BooleanArray const *const booleanArray = message->getBodyData()->asBooleanArray();
//    BOOST_CHECK_EQUAL(booleanArray);
//    BOOST_CHECK_EQUAL(booleanArray->typeId()  == BOOLEAN_ARRAY_ID);
//
//
//     boost::dynamic_bitset<> cVector01;
//    BOOST_CHECK_EQUAL(booleanArray->copyTo(cVector01));
//    BOOST_CHECK_EQUAL(cVector01.size() == 100000U);
//
//
//    for (int var = 0; var < int(cVector01.size()); ++var) {
//        BOOST_CHECK_EQUAL(cVector01[var] == true);
//    }
//
//    msg->release();
//    outputMsg->release();
//}
//#endif
//
