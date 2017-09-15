// +++ -------------------------------------------------------------------------
#include "mvcmodelcmake_jtenv.hpp"

#include "projectconf_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelCMake::MvcModelCMake () :
    jkpp::MvcModelImpl(),
    m_confFilePath {(getConfDirPath() / "cmake.conf").string()},
    m_cmakeCmds {}
{
}
// -----------------------------------------------------------------------------
std::string MvcModelCMake::getCommand (const std::string& aName)
{
	auto cmd {m_cmakeCmds.find(aName)};
	std::string result {};
    if (cmd != m_cmakeCmds.end()) result = cmd->second;

    return result;
}
// -----------------------------------------------------------------------------
bool MvcModelCMake::addCommand (const std::string& aName, const std::string& aCommand)
{
	if (aCommand.empty()) return false;
    if (aName.empty()) return false;
	if (m_cmakeCmds.find(aName) != m_cmakeCmds.end()) return false;

    m_cmakeCmds.insert(std::make_pair(aName, aCommand));
    return true;
}
// -----------------------------------------------------------------------------
bool MvcModelCMake::removeCommand (const std::string& aName)
{
	if (m_cmakeCmds.find(aName) == m_cmakeCmds.end()) return false;

    m_cmakeCmds.erase(m_cmakeCmds.find(aName));
    return true;
}
// -----------------------------------------------------------------------------
bool MvcModelCMake::load ()
{
    std::ifstream file {m_confFilePath, std::fstream::in};
    if (!file) return false;

    beginUpdate();
    bool result {loadLines (file)};
    endUpdate();

	return result;
}
// -----------------------------------------------------------------------------
bool MvcModelCMake::loadLines (std::ifstream& aFile)
{
    std::string line {};
    while (std::getline(aFile, line)) {
    	if (!line.empty()) {
            auto pos {line.find_first_of('=')};
            if (pos == std::string::npos) return false;
            std::string key {line.substr(0, pos)};
            std::string value {line.substr(pos + 1)};

            if (m_cmakeCmds.find(key) != m_cmakeCmds.end()) return false;

            m_cmakeCmds.insert(std::make_pair(key, value));
        }
    }
    return aFile.eof();
}
// -----------------------------------------------------------------------------
bool MvcModelCMake::save ()
{
    std::ofstream file {m_confFilePath, std::fstream::out};
    if (!file) return false;

    for (auto cmd : m_cmakeCmds) file << cmd.first << "=" << cmd.second << '\n';

    file.close();

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
