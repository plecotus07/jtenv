// +++ -------------------------------------------------------------------------
#include "mvcmodelconfig_jtenv.hpp"

#include "projectconf_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelConfig::MvcModelConfig () :
    jkpp::MvcModelImpl(),
    m_confFilePath {(getConfDirPath() / "main.conf").string()},
    m_userName {},
    m_userEmail {}
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
bool MvcModelConfig::load ()
{
    std::ifstream file {m_confFilePath, std::fstream::in};
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
        else return false;
    }
    return aFile.eof();
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::save ()
{
    std::ofstream file {m_confFilePath, std::fstream::out};
    if (!file) return false;

    file << "user_name=" << m_userName << '\n';
    file << "user_email=" << m_userEmail << '\n';

    file.close();

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
