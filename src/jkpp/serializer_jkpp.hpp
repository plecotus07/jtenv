// +++ -------------------------------------------------------------------------
#ifndef SERIALIZER_JKPP_HPP
#define SERIALIZER_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include "serializeriface_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class Serializer : public SerializerIface {
	public:
    	Serializer ();

        virtual void openForRead (std::istream& aStream);
        virtual void openForWrite (std::ostream& aStream);

        virtual void close ();

        virtual void serializeString (const std::string& aName, std::string& aValue);
        virtual void serializeCsvString (const std::string& aName, char aDelim, std::vector<std::string> aValues);

	protected:
        virtual SerializerIface::SPtr getMode () = 0;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // SERIALIZER_JKPP_HPP
// +++ -------------------------------------------------------------------------
