// +++ -------------------------------------------------------------------------
#include "serializer_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
Serializer::Serializer ()
{
}
// -----------------------------------------------------------------------------
void Serializer::openForRead (std::istream& aStream)
{
    getMode()->openForRead(aStream);
}
// -----------------------------------------------------------------------------
void Serializer::openForWrite (std::ostream& aStream)
{
	getMode()->openForWrite(aStream);
}
// -----------------------------------------------------------------------------
void Serializer::close ()
{
	getMode()->close();
}
// -----------------------------------------------------------------------------
void Serializer::serializeString (const std::string& aName, std::string& aValue)
{
	getMode()->serializeString(aName, aValue);
}
// -----------------------------------------------------------------------------
void Serializer::serializeCsvString (const std::string& aName, const std::string& aDelims, std::vector<std::string>& aValues)
{
	getMode()->serializeCsvString(aName, aDelims, aValues);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
