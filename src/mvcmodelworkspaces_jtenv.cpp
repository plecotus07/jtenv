// +++ -------------------------------------------------------------------------
#include "mvcmodelworkspaces_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelWorkspaces::MvcModelWorkspaces () :
    jkpp::MvcModelImpl(),
    m_workspaces {},
    m_confFilePath {(getConfDirPath() / "workspaces.conf").string()},
    m_workspacesDirPath {getConfDirPath() / "workspaces"}
{
}
// -----------------------------------------------------------------------------
Workspace::SPtr MvcModelWorkspaces::getWorkspace (const std::string& aName)
{
	auto found {m_workspaces.find(aName)};

	if (found == m_workspaces.end()) return nullptr;

	return found->second;
}
// -----------------------------------------------------------------------------
Workspace::SPtr MvcModelWorkspaces::addWorkspace (const std::string& aName, const fs::path& aPath)
{
    if (m_workspaces.find(aName) != m_workspaces.end()) return Workspace::SPtr(nullptr);

    beginUpdate();
    Workspace::SPtr workspace {std::make_shared<Workspace>(aName, aPath)};
    m_workspaces.insert(std::make_pair(aName, workspace));
    endUpdate();

    return workspace;
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::load ()
{
    m_workspaces.clear();
	if (!fs::exists(m_workspacesDirPath)) return false;

    fs::directory_iterator dir { m_workspacesDirPath };

    for (;dir != fs::directory_iterator(); ++dir) {
        if ( (fs::is_directory(dir->path()))
		     && (dir->path().extension() == ".git") ) {
			if (!addWorkspace(dir->path().stem().string())) return false;
        }
    }

    std::ifstream file {m_confFilePath.c_str(), std::fstream::in};
    if (!file) return false;

    beginUpdate();
    bool result {loadLines (file)};
    endUpdate();

	return result;
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::save ()
{
    std::ofstream file {m_confFilePath.c_str(), std::fstream::out};
    if (!file) return false;

    for (auto ws : m_workspaces) file << "workspace=" << ws.first << ':' << ws.second->getPath().string() << '\n';
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::clean ()
{
	bool result {false};
	for (auto ws = m_workspaces.begin() ; ws != m_workspaces.end(); ++ws) {
    	if (!fs::exists(ws->second->getPath())) {
        	m_workspaces.erase(ws);
            result = true;
        }
    }

    return result;
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::loadLines (std::ifstream& aFile)
{
    std::string line {};
    while (std::getline(aFile, line)) {
        auto pos {line.find_first_of('=')};
        if (pos == std::string::npos) return false;
        std::string key {line.substr(0, pos)};
        std::string value {line.substr(pos + 1)};

        if (key == "workspace") {
            auto ws_pos {value.find_first_of(':')};
            if (ws_pos == std::string::npos) return false;

            std::string name {value.substr(0, ws_pos)};
            std::string path {value.substr(ws_pos + 1)};

            auto ws {m_workspaces.find(name)};
            if (ws != m_workspaces.end()) ws->second->setPath(path);
            else if (!addWorkspace(name, path)) return false;
        }
        else return false;
    }
    return aFile.eof();
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
