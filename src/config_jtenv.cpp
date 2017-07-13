// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"
#include "filesystem_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ConfigMainFile::ConfigMainFile (const fs::path& aConfigDirPath, std::string& aWorkspacesUrl, std::string& aUserName, std::string& aUserEmail) :
	jkpp::ConfigFile {aConfigDirPath / "main.conf"},
	m_workspacesUrl {aWorkspacesUrl},
	m_userName {aUserName},
	m_userEmail {aUserEmail}
{
}
// -----------------------------------------------------------------------------
void ConfigMainFile::setDefaultValues ()
{
	m_workspacesUrl = jkpp::getHomeDirPath();
	m_userName = "";
	m_userEmail = "";
}
// -----------------------------------------------------------------------------
bool ConfigMainFile::setValue (const std::string& aKey, const std::string& aValue)
{
	try {
		if (aKey == "workspaces_url")   m_workspacesUrl = aValue;
		else if (aKey == "user_name")  m_userName = aValue;
		else if (aKey == "user_email") m_userEmail = aValue;
		else return false;
	}
	catch (...) {
		return false;
	}
	return true;
}
// -----------------------------------------------------------------------------
bool ConfigMainFile::saveValues (std::ofstream& aFileStream) const
{
	aFileStream << "workspaces_url=" << m_workspacesUrl << '\n'
	            << "user_name=" << m_userName << '\n'
	            << "user_email=" << m_userEmail << '\n';

	return true;
}
// -----------------------------------------------------------------------------
void ConfigMainFile::clearValues ()
{
	m_workspacesUrl.clear();
	m_userName.clear();
	m_userEmail.clear();
}
// +++ -------------------------------------------------------------------------
ConfigWorkspacesFile::ConfigWorkspacesFile (const fs::path& aConfigDirPath, std::map<std::string, fs::path>& aWorkspaces) :
	ConfigFile {aConfigDirPath / "workspaces.conf"},
	m_workspaces {aWorkspaces}
{
}
// -----------------------------------------------------------------------------
void ConfigWorkspacesFile::setDefaultValues ()
{
	m_workspaces.clear();
}
// -----------------------------------------------------------------------------
bool ConfigWorkspacesFile::setValue (const std::string& aKey, const std::string& aValue)
{
	if (aKey == "workspace") {
		auto sepPos {aValue.find_first_of(";")};
		std::string wsName {aValue.substr(0, sepPos)};
		fs::path wsPath {aValue.substr(sepPos + 1)};
		m_workspaces.insert(std::make_pair(wsName, wsPath));
	}
	else return false;

	return true;
}
// -----------------------------------------------------------------------------
bool ConfigWorkspacesFile::saveValues (std::ofstream& aFileStream) const
{
	for (auto ws : m_workspaces) aFileStream << "workspace=" << ws.first << ";" << ws.second.string() << '\n';

	return true;
}
// -----------------------------------------------------------------------------
void ConfigWorkspacesFile::clearValues ()
{
	m_workspaces.clear();
}
// +++ -------------------------------------------------------------------------
Config::Config (const fs::path& aConfigDirPath) :
	jkpp::Config(aConfigDirPath)
{
}
// -----------------------------------------------------------------------------
void Config::init()
{
	m_configFiles.push_back(std::make_unique<ConfigMainFile>(m_configDirPath));
	m_configFiles.push_back(std::make_unique<ConfigWorkspacesFile>(m_configDirPath));
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
