// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"
#include "filesystem_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ConfigMainFile::ConfigMainFile (const fs::path& aConfigDirPath, std::string& aWorkspacesUrl, std::string& aUserName, std::string& aUserEmail) :
	jkpp::ConfigFile {aConfigDirPath / "main.conf"}
{
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<fs::path>>("workspaces_url", aWorkspacesUrl, (aConfigDirPath / "workspaces").string()));
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<std::string>>("user_name", aUserName, ""));
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<std::string>>("user_email", aUserEmail, ""));
}
// -----------------------------------------------------------------------------
ConfigWorkspacesFile::ConfigWorkspacesFile (const fs::path& aConfigDirPath, std::map<std::string, fs::path>& aWorkspaces) :
	ConfigFile {aConfigDirPath / "workspaces.conf"}
{
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<std::map<std:string, std::string>>>("workspace", aWorkspaces);
}
// +++ -------------------------------------------------------------------------
Config::Config (const fs::path& aConfigDirPath) :
    jkpp::Config(aConfigDirPath),
    m_workspacesUrl {},
    m_userName {},
    m_userEmail {},
    m_workspaces
{
}
// -----------------------------------------------------------------------------
void Config::init()
{
	m_configFiles.push_back(std::make_unique<ConfigMainFile>(m_configDirPath, m_workspacesUrl, m_userName, m_userEmail));
	m_configFiles.push_back(std::make_unique<ConfigWorkspacesFile>(m_configDirPath, m_workspaces));
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
