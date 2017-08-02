// +++ -------------------------------------------------------------------------
#ifndef CONFIG_JTENV_HPP
#define CONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <config_jkpp.hpp>
// -----------------------------------------------------------------------------
#include <map>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class ConfigMainFile : public jkpp::ConfigFile {
	public:
		ConfigMainFile (const fs::path& aConfigDirPath, fs::path& aWorkspacesUrl, std::string& aUserName, std::string& aUserEmail);
};
// +++ -------------------------------------------------------------------------
class ConfigWorkspacesFile : public jkpp::ConfigFile {
	public:
		ConfigWorkspacesFile (const fs::path& aConfigDirPath, std::map<std::string, fs::path>& aWorkspaces);

	protected:
};
// +++ -------------------------------------------------------------------------
class Config : public jkpp::Config {
	public:
		Config (const fs::path& aConfigDirPath);

		const std::string& getUserName () const { return m_userName; }
		void               setUserName (const std::string& aUserName) { m_userName = aUserName; }

		virtual void init ();

	protected:
		fs::path                        m_workspacesUrl;
		std::string                     m_userName;
		std::string                     m_userEmail;
		std::map<std::string, fs::path> m_workspaces;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // CONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
