// +++ -------------------------------------------------------------------------
#ifndef CONFIG_JTENV_HPP
#define CONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "config_jkpp.hpp"
// -----------------------------------------------------------------------------
#include <map>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class ConfigMainFile : public jkpp::ConfigFile {
	public:
		ConfigMainFile (const fs::path& aConfigDirPath, std::string& aWorkspacesUrl, std::string& aUserName, std::string& aUserEmail);

		virtual void setDefaultValues ();

	protected:
		virtual bool setValue (const std::string& aKey, const std::string& aValue);
		virtual bool saveValues (std::ofstream& aFileStream) const;
		virtual void clearValues ();

		std::string& m_workspacesUrl;
		std::string& m_userName;
		std::string& m_userEmail;
};
// +++ -------------------------------------------------------------------------
class ConfigWorkspacesFile : public jkpp::ConfigFile {
	public:
		ConfigWorkspacesFile (const fs::path& aConfigDirPath, std::map<std::string, fs::path>& aWorkspaces);

		virtual void setDefaultValues ();

	protected:
		virtual bool setValue (const std::string& aKey, const std::string& aValue);
		virtual bool saveValues (std::ofstream& aFileStream) const;
		virtual void clearValues ();

		std::map<std::string, fs::path>& m_workspaces;
};
// +++ -------------------------------------------------------------------------
class Config : public jkpp::Config {
	public:
		Config (const fs::path& aConfigDirPath);

		virtual void init ();

	protected:
		std::string                     m_workspacesUrl;
		std::string                     m_userName;
		std::string                     m_userEmail;
		std::map<std::string, fs::path> m_workspaces;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // CONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
