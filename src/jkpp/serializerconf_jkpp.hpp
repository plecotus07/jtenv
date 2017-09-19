// +++ -------------------------------------------------------------------------
#ifndef SERIALIZERCONF_JKPP_HPP
#define SERIALIZERCONF_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include "serializer_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class SerializerConf : public Serializer {
	friend class SerializerConfModeClosed;
	friend class SerializerConfModeRead;
	friend class SerializerConfModeWrite;
	public:
    	SerializerConf ();

	protected:
		virtual SerializerIface::SPtr getMode () { return m_mode; }

		SerializerIface::SPtr m_mode;
};
// +++ -------------------------------------------------------------------------
class SerializerConfModeClosed : public SerializerIface {
    public:
    	SerializerConfModeClosed (SerializerConf& aSerializer);

        virtual void openForRead (std::istream& aStream);
        virtual void openForWrite (std::ostream& aStream);

        virtual void close ();

        virtual void serializeString (const std::string& aName, std::string& aValue);
        virtual void serializeCsvString (const std::string& aName, char aDelim, std::vector<std::string> aValues);

    protected:
    	SerializerConf& m_serializer;
};
// +++ -------------------------------------------------------------------------
class SerializerConfModeRead : public SerializerIface {
    public:
    	SerializerConfModeRead (SerializerConf& aSerializer, std::istream& aStream);

        virtual void openForRead (std::istream& aStream);
        virtual void openForWrite (std::ostream& aStream);

        virtual void close ();

        virtual void serializeString (const std::string& aName, std::string& aValue);
        virtual void serializeCsvString (const std::string& aName, char aDelim, std::vector<std::string> aValues);

    protected:
    	SerializerConf& m_serializer;
        std::istream&   m_stream;

		std::pair<std::string, std::string> serializeKeyValue (bool aQuoted);
};
// +++ -------------------------------------------------------------------------
class SerializerConfModeWrite : public SerializerIface {
    public:
    	SerializerConfModeWrite (SerializerConf& aSerializer, std::ostream& aStream);

        virtual void openForRead (std::istream& aStream);
        virtual void openForWrite (std::ostream& aStream);

        virtual void close ();

        virtual void serializeString (const std::string& aName, std::string& aValue);
        virtual void serializeCsvString (const std::string& aName, char aDelim, std::vector<std::string> aValues);

    protected:
    	SerializerConf& m_serializer;
    	std::ostream&   m_stream;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // SERIALIZERCONF_JKPP_HPP
// +++ -------------------------------------------------------------------------
