// +++ -------------------------------------------------------------------------
#ifndef SERIALIZERIFACE_JKPP_HPP
#define SERIALIZERIFACE_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include <memory>
#include <vector>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class SerializerIface {
	public:
    	using SPtr = std::shared_ptr<SerializerIface>;

		virtual ~SerializerIface () = default;

        virtual void openForRead (std::istream& aStream) = 0;
        virtual void openForWrite (std::ostream& aStream) = 0;

        virtual void close () = 0;

        virtual void serializeString (const std::string& aName, std::string& aValue) = 0;
        virtual void serializeCsvString (const std::string& aName, const std::string& aDelims, std::vector<std::string>& aValues) = 0;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // SERIALIZERIFACE_JKPP_HPP
// +++ -------------------------------------------------------------------------
