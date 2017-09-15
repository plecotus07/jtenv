// +++ -------------------------------------------------------------------------
#ifndef CONFIG_JKPP_HPP
#define CONFIG_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include <string>
#include <map>
#include <vector>
#include <boost/filesystem.hpp>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jkpp {
// +++ -------------------------------------------------------------------------
class ConfigFileField {
	public:
		using UPtr = std::unique_ptr<ConfigFileField>;

		ConfigFileField (const std::string& aKey) : m_key{aKey} {};

		virtual const std::string& getKey () const { return m_key; }

		virtual bool setValue (const std::string& aValue) = 0;
		virtual bool saveValue (std::ofstream& aFileStream) = 0;
		virtual void clearValue () = 0;
		virtual void setDefaultValue () = 0;

	protected:
		std::string m_key;
};
// +++ -------------------------------------------------------------------------
template <class T>
class ConfigFileFieldImpl : public ConfigFileField {
	public:
		ConfigFileFieldImpl (const std::string& aKey, T& aValue, const T& aDefaultValue) : ConfigFileField(aKey), m_value{aValue}, m_defaultValue(aDefaultValue) {};

		virtual bool setValue (const std::string& aValue);
		virtual bool saveValue (std::ofstream& aFileStream);
		virtual void clearValue ();
		virtual void setDefaultValue ();

	protected:
		T& m_value;
		T  m_defaultValue;

};
// -----------------------------------------------------------------------------
template <class T>
void ConfigFileFieldImpl<T>::setDefaultValue ()
{
	m_value = m_defaultValue;
}
// -----------------------------------------------------------------------------
template <class T>
bool ConfigFileFieldImpl<T>::saveValue (std::ofstream& aFileStream)
{
	aFileStream << m_key << "=" << m_value << '\n';
	return !aFileStream.fail();
}
// -----------------------------------------------------------------------------
template <class U, class V>
class ConfigFileFieldImpl<std::map<U, V>> : public ConfigFileField {
	public:
		ConfigFileFieldImpl (const std::string& aKey, std::map<U, V>& aValue, char aSeparator, const std::map<U, V>& aDefaultValue) : ConfigFileField(aKey), m_value{aValue}, m_separator{aSeparator}, m_defaultValue{aDefaultValue} {};

		virtual bool setValue (const std::string& aValue);
		virtual bool saveValue (std::ofstream& aFileStream);
		virtual void clearValue ();
		virtual void setDefaultValue ();

	protected:
		std::map<U, V>& m_value;
		char            m_separator;
		std::map<U, V>  m_defaultValue;

};
// -----------------------------------------------------------------------------
template <class U, class V>
void ConfigFileFieldImpl<std::map<U, V>>::setDefaultValue ()
{
	m_value = m_defaultValue;
}
// -----------------------------------------------------------------------------
template <class U, class V>
void ConfigFileFieldImpl<std::map<U, V>>::clearValue ()
{
	m_value.clear();
}
// -----------------------------------------------------------------------------
template <class U, class V>
bool ConfigFileFieldImpl<std::map<U, V>>::saveValue (std::ofstream& aFileStream)
{
	for (auto value : m_value) {
		if  (!(aFileStream << m_key << "=" << value.first << m_separator << value.second << '\n'))
			return false;
	}
	return true;
}
// +++ -------------------------------------------------------------------------
template <class U>
class ConfigFileFieldImpl<std::vector<U>> : public ConfigFileField {
	public:
		ConfigFileFieldImpl (const std::string& aKey, std::vector<U>& aValue, const std::vector<U>& aDefaultValue) : ConfigFileField(aKey), m_value{aValue}, m_defaultValue{aDefaultValue} {};

		virtual bool setValue (const std::string& aValue);
		virtual bool saveValue (std::ofstream& aFileStream);
		virtual void clearValue ();
		virtual void setDefaultValue ();

	protected:
		std::vector<U>& m_value;
		char            m_separator;
		std::vector<U>  m_defaultValue;

};
// -----------------------------------------------------------------------------
template <class U>
void ConfigFileFieldImpl<std::vector<U>>::setDefaultValue ()
{
	m_value = m_defaultValue;
}
// -----------------------------------------------------------------------------
template <class U>
bool ConfigFileFieldImpl<std::vector<U>>::saveValue (std::ofstream& aFileStream)
{
	for (auto value : m_value) {
		if  (!(aFileStream << m_key << "=" << value << '\n'))
			return false;
	}
	return true;
}
// -----------------------------------------------------------------------------
template <class U>
void ConfigFileFieldImpl<std::vector<U>>::clearValue ()
{
	m_value.clear();
}
// +++ -------------------------------------------------------------------------
class ConfigFile {
	public:
		using UPtr = std::unique_ptr<ConfigFile>;
		ConfigFile (const fs::path& aFilePath);

		bool         load ();
		bool         save () const;
		virtual void setDefaultValues ();

	protected:
		virtual bool setValue (const std::string& aKey, const std::string& aValue);
		virtual bool saveValues (std::ofstream& aFileStream) const;
		virtual void clearValues ();

		fs::path                           m_path;
		std::vector<ConfigFileField::UPtr> m_fields;
};
// +++ -------------------------------------------------------------------------
class Config {
	public:
		using UPtr = std::unique_ptr<Config>;

		Config (const fs::path& aConfigDirPath);

		virtual void init () = 0;

		bool load ();
		bool save () const;

		void setDefaults ();

	protected:
		fs::path                       m_configDirPath;
		std::vector <ConfigFile::UPtr> m_configFiles;
};
// +++ -------------------------------------------------------------------------
} // jtcs
// +++ -------------------------------------------------------------------------
#endif // CONFIG_JTCS_HPP
// +++ -------------------------------------------------------------------------
