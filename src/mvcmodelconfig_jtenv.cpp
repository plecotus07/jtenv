// +++ -------------------------------------------------------------------------
#include "mvcmodelconfig_jtenv.hpp"

#include "projectconf_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelConfig::MvcModelConfig () :
    jkpp::MvcModelImpl(),
    m_userName {},
    m_userEmail {},
    m_workspacesDirPath {getConfDirPath() / "workspaces"},
    m_confFilePath {(getConfDirPath() / "main.conf").string()}
{
}
// -----------------------------------------------------------------------------
void MvcModelConfig::setUserName (const std::string& aUserName)
{
    beginUpdate();
	m_userName = aUserName;
    endUpdate();
}
// -----------------------------------------------------------------------------
void MvcModelConfig::setUserEmail (const std::string& aUserEmail)
{
    beginUpdate();
    m_userEmail = aUserEmail;
    endUpdate();
}
// -----------------------------------------------------------------------------
void MvcModelConfig::setWorkspacesDirPath (const fs::path& aWorkspacesDirPath)
{
    beginUpdate();
    m_workspacesDirPath = aWorkspacesDirPath;
    endUpdate();
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::load ()
{
    std::ifstream file {m_confFilePath.c_str(), std::fstream::in};
    if (!file) return false;

    beginUpdate();
    bool result {loadLines (file)};
    endUpdate();

	return result;
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::loadLines (std::ifstream& aFile)
{
    std::string line {};
    while (std::getline(aFile, line)) {
        auto pos {line.find_first_of('=')};
        if (pos == std::string::npos) return false;
        std::string key {line.substr(0,pos)};
        std::string value {line.substr(pos + 1)};

        if (key == "user_name") m_userName = value;
        else if (key == "user_email") m_userEmail = value;
        else if (key == "workspaces_dir_path") m_workspacesDirPath = value;
        else return false;
    }
    return aFile.eof();
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::save ()
{
    std::ofstream file {m_confFilePath.c_str(), std::fstream::out};
    if (!file) return false;

    file << "user_name=" << m_userName << '\n';
    file << "user_email" << m_userEmail << '\n';
    file << "workspaces_dir_path" << m_workspacesDirPath << '\n';

    file.close();

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
