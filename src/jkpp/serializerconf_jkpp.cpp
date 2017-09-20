// +++ -------------------------------------------------------------------------
#include "serializerconf_jkpp.hpp"
//#include <istream>
//#include <ostream>
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
SerializerConf::SerializerConf () :
    m_mode {std::make_shared<SerializerConfModeClosed>(*this)}
{
}
// +++ -------------------------------------------------------------------------
SerializerConfModeClosed::SerializerConfModeClosed (SerializerConf& aSerializer) : m_serializer(aSerializer)
{
}
// -----------------------------------------------------------------------------
void SerializerConfModeClosed::openForRead (std::istream& aStream)
{
    m_serializer.m_mode = std::make_shared<SerializerConfModeRead>(m_serializer, aStream);
}
// -----------------------------------------------------------------------------
void SerializerConfModeClosed::openForWrite (std::ostream& aStream)
{
    m_serializer.m_mode = std::make_shared<SerializerConfModeWrite>(m_serializer, aStream);
}
// -----------------------------------------------------------------------------
void SerializerConfModeClosed::close ()
{
	throw std::runtime_error("SerializerConfModeClosed::Close");
}
// -----------------------------------------------------------------------------
void SerializerConfModeClosed::serializeString (const std::string& , std::string& )
{
	throw std::runtime_error("SerializerConfModeClosed::serializeString");
}
// -----------------------------------------------------------------------------
void SerializerConfModeClosed::serializeCsvString (const std::string& , const std::string& , std::vector<std::string>& )
{
	throw std::runtime_error("SerializerConfModeClosed::serializeCsvString");
}
// +++ -------------------------------------------------------------------------
SerializerConfModeRead::SerializerConfModeRead (SerializerConf& aSerializer, std::istream& aStream) :
    m_serializer {aSerializer},
    m_stream {aStream}
{
}
// -----------------------------------------------------------------------------
void SerializerConfModeRead::openForRead (std::istream& )
{
	throw std::runtime_error("SerializerConfModeRead::openForRead");
}
// -----------------------------------------------------------------------------
void SerializerConfModeRead::openForWrite (std::ostream& )
{
	throw std::runtime_error("SerializerConfModeRead::openForWrite");
}
// -----------------------------------------------------------------------------
void SerializerConfModeRead::close ()
{
    m_serializer.m_mode = std::make_shared<SerializerConfModeClosed>(m_serializer);
}
// -----------------------------------------------------------------------------
void SerializerConfModeRead::serializeString (const std::string& aName, std::string& aValue)
{
	auto kv {serializeKeyValue(true)};
    std::cerr << "+++: name=" << kv.first << '\n';

    if (kv.first != aName) throw std::runtime_error("SerializerConfModeRead::serializeString: invalid name");

	aValue = kv.second;
}
// -----------------------------------------------------------------------------
void SerializerConfModeRead::serializeCsvString (const std::string& aName, const std::string& aDelims, std::vector<std::string>& aValues)
{
	auto kv {serializeKeyValue(true)};
    if (kv.first != aName) throw std::runtime_error("SerializerConfModeRead::serializeCsvString: invalid name");
    std::string delims {aDelims};

    std::string::size_type prev {};
    std::string::size_type pos {};

    do {
	    pos = kv.second.find_first_of(delims, prev);
        aValues.push_back(kv.second.substr(prev, pos - prev));
        prev = pos + 1;
    } while (pos != std::string::npos);
}
// -----------------------------------------------------------------------------
std::pair<std::string, std::string> SerializerConfModeRead::serializeKeyValue (bool aQuoted)
{
	std::string buf {};
    char c {};

	while (m_stream.get(c) && (c == '\n'));

    if (!m_stream) throw std::runtime_error("SerializerConfModeRead::serializeKeyValue: file error");
    m_stream.putback(c);

	while (m_stream.get(c) && (c != '=') && (c != '\n')) {
		buf += c;
    }

    if (!m_stream) throw std::runtime_error("SerializerConfModeRead::serializeKeyValue: file error");
    if (buf.empty()) throw std::runtime_error("SerializerConfModeRead::serializeKeyValue: empty key");
    if (c == '\n') throw std::runtime_error("SerializerConfModeRead::serializeKeyValue: invalid key");

    std::string name {buf};

    char delim {'\n'};
	if (aQuoted) {
	    if (!m_stream.get(c)) throw std::runtime_error("SerializerConfModeRead::serializeKeyValue: file error");
	    if (c != '"') throw std::runtime_error("SerializerConfModeRead::serializeKeyValue: invalid format");

        delim = '"';
    }

    buf.clear();
    while (m_stream.get(c) && (c != delim)) {
		buf += c;
    }

    if (!m_stream) throw std::runtime_error("SerializerConfModeRead::serializeKeyValue: file error");

	return std::make_pair(name, buf);
}
// +++ -------------------------------------------------------------------------
SerializerConfModeWrite::SerializerConfModeWrite (SerializerConf& aSerializer, std::ostream& aStream) :
    m_serializer {aSerializer},
    m_stream {aStream}
{
}
// -----------------------------------------------------------------------------
void SerializerConfModeWrite::openForRead (std::istream& )
{
	throw std::runtime_error("SerializerConfModeWrite::openForRead");
}
// -----------------------------------------------------------------------------
void SerializerConfModeWrite::openForWrite (std::ostream& )
{
	throw std::runtime_error("SerializerConfModeWrite::openForWrite");
}
// -----------------------------------------------------------------------------
void SerializerConfModeWrite::close ()
{
    m_serializer.m_mode = std::make_shared<SerializerConfModeClosed>(m_serializer);
}
// -----------------------------------------------------------------------------
void SerializerConfModeWrite::serializeString (const std::string& aName, std::string& aValue)
{
	m_stream << aName << "=\"" << aValue << "\"\n";
}
// -----------------------------------------------------------------------------
void SerializerConfModeWrite::serializeCsvString (const std::string& aName, const std::string& aDelims, std::vector<std::string>& aValues)
{
	m_stream << aName << "=\"";
    bool first {true};
    for (auto v : aValues) {
    	if (first) first = false;
        else m_stream << aDelims;

    	m_stream << v;
    }

    m_stream << "\"\n";
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
