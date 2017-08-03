// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"
#include "filesystem_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<std::map<std::string, fs::path>>::setValue (const std::string& aValue)
{
	auto sepPos = aValue.find_first_of(m_separator);
	if (sepPos == std::string::npos) return false;

	try {
		m_value.insert(std::make_pair(aValue.substr(0, sepPos), fs::path(aValue.substr(sepPos + 1))));
	} catch (...) {
		return false;
	}

	return true;
}

// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ConfigMainFile::ConfigMainFile (const fs::path& aConfigDirPath, std::string& aWorkspacesUrl, std::string& aUserName, std::string& aUserEmail) :
	jkpp::ConfigFile {aConfigDirPath / "main.conf"}
{
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<std::string>>("workspaces_url", aWorkspacesUrl, (aConfigDirPath / "workspaces").string()));
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<std::string>>("user_name", aUserName, ""));
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<std::string>>("user_email", aUserEmail, ""));
}
// -----------------------------------------------------------------------------
ConfigWorkspacesFile::ConfigWorkspacesFile (const fs::path& aConfigDirPath, std::map<std::string, fs::path>& aWorkspaces) :
	ConfigFile {aConfigDirPath / "workspaces.conf"}
{
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<std::map<std::string, fs::path>>>("workspace", aWorkspaces, '|', std::map<std::string, fs::path>()));
}
// +++ -------------------------------------------------------------------------
Config::Config (const fs::path& aConfigDirPath) :
    jkpp::Config(aConfigDirPath),
    m_workspacesUrl {},
    m_userName {},
    m_userEmail {},
    m_workspaces {}
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
