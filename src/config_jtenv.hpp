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
		ConfigMainFile (const fs::path& aConfigDirPath, fs::path& aWorkspacesDirPath, std::string& aUserName, std::string& aUserEmail);
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
    	using UPtr = std::unique_ptr<Config>;

		Config (const fs::path& aConfigDirPath);
		Config (const Config& aOther) = delete;

        Config& operator= (const Config& aOther) = delete;


		const std::string& getUserName () const { return m_userName; }
		void               setUserName (const std::string& aUserName) { m_userName = aUserName; }

		const std::string& getUserEmail () const { return m_userEmail; }
		void               setUserEmail (const std::string& aUserEmail) { m_userEmail = aUserEmail; }

		const fs::path&    getWorkspacesDirPath () const { return m_workspacesDirPath; }
		void               setWorkspacesDirPath (const fs::path& aWorkspacesDirPath) { m_workspacesDirPath = aWorkspacesDirPath; }

        fs::path           getWsPath (const std::string& aName) const;
        std::string        getWsName (const fs::path& aPath) const;

		virtual void init ();

	protected:
		fs::path                        m_workspacesDirPath;
		std::string                     m_userName;
		std::string                     m_userEmail;
		std::map<std::string, fs::path> m_workspaces;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // CONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
