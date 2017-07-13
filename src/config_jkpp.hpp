// +++ -------------------------------------------------------------------------
#ifndef CONFIG_JKPP_HPP
#define CONFIG_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include <string>
#include <boost/filesystem.hpp>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jkpp {
// +++ -------------------------------------------------------------------------
class ConfigFile {
	public:
		using UPtr = std::unique_ptr<ConfigFile>;
		ConfigFile (const fs::path& aFilePath);

		virtual bool load ();
		virtual bool save () const;
		virtual void setDefaultValues () = 0;

	protected:
		virtual bool setValue (const std::string& aKey, const std::string& aValue) = 0;
		virtual bool saveValues (std::ofstream& aFileStream) const = 0;
		virtual void clearValues () = 0;
		fs::path m_path;
};
// +++ -------------------------------------------------------------------------
class Config {
	public:
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
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // CONFIG_JKPP_HPP
// +++ -------------------------------------------------------------------------
