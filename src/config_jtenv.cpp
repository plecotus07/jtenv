// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"
#include "filesystem_jkpp.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
template <>
bool ConfigFileFieldImpl<fs::path>::setValue (const std::string& aValue)
{
	m_value = aValue;
	return true;
}
// -----------------------------------------------------------------------------
template <>
void ConfigFileFieldImpl<fs::path>::clearValue ()
{
	m_value.clear();
}
// -----------------------------------------------------------------------------
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
ConfigMainFile::ConfigMainFile (const fs::path& aConfigDirPath, fs::path& aWorkspacesDirPath, std::string& aUserName, std::string& aUserEmail) :
	jkpp::ConfigFile {aConfigDirPath / "main.conf"}
{
	m_fields.push_back(std::make_unique<jkpp::ConfigFileFieldImpl<fs::path>>("workspaces_dir_path", aWorkspacesDirPath, (aConfigDirPath / "workspaces").string()));
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
    m_workspacesDirPath {},
    m_userName {},
    m_userEmail {},
    m_workspaces {}
{
}
// -----------------------------------------------------------------------------
fs::path Config::getWsPath (const std::string& aName) const
{
	auto ws {m_workspaces.find(aName)};

    if (ws == m_workspaces.end()) return fs::path();

    return ws->second;
}
// -----------------------------------------------------------------------------
std::string Config::getWsName (const fs::path& aPath) const
{
	for (auto ws : m_workspaces) {
    	fs::path wsPath {ws.second};
        fs::path path {aPath};

        if (wsPath.filename() == "." ) wsPath.remove_filename();

        path.remove_filename();

       auto wsPathLen {std::distance(wsPath.begin(), wsPath.end())};
       auto pathLen {std::distance(path.begin(), path.end())};

       if (wsPathLen > pathLen) continue;

       if (std::equal(wsPath.begin(), wsPath.end(), path.begin())) return ws.first;
    }

    return "";
}
// -----------------------------------------------------------------------------
void Config::init()
{
	m_configFiles.push_back(std::make_unique<ConfigMainFile>(m_configDirPath, m_workspacesDirPath, m_userName, m_userEmail));
	m_configFiles.push_back(std::make_unique<ConfigWorkspacesFile>(m_configDirPath, m_workspaces));
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
