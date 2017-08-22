// +++ -------------------------------------------------------------------------
#include "mvcmodelworkspaces_jtenv.hpp"

#include "projectconf_jtenv.hpp"
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
Item::SPtr MvcModelWorkspaces::getItem (const std::string& aAddr, const fs::path& aPath)
{
	auto pos {aAddr.find_first_of(':')};

	std::string proj_name {};
	std::string ws_name {};

	if (pos == std::string::npos) ws_name = aAddr;
	else {
		ws_name = aAddr.substr(0, pos);
		proj_name = aAddr.substr(pos + 1);
	}

	if (ws_name.empty() && proj_name.empty()) {
		fs::path dir {aPath};
		for (; !dir.empty() && !fs::exists(dir / "project.conf"); dir = dir.parent_path());
		if (dir.empty()) return nullptr;

		proj_name = dir.filename().string();

		if (dir.parent_path().empty()) return nullptr;

		ws_name = dir.parent_path().filename().string();

	} else if (ws_name.empty()) {
		fs::path dir {aPath};
		for (; !dir.empty() && !fs::exists(dir / proj_name / "project.conf"); dir = dir.parent_path());

		if (dir.parent_path().empty()) return nullptr;
		ws_name = dir.filename().string();

	} else if (proj_name.empty()) {
		return getWorkspace(ws_name);
	}

	Workspace::SPtr ws = getWorkspace(ws_name);
	if (!ws) return nullptr;

	return ws->getProject(proj_name);
}
// -----------------------------------------------------------------------------
Workspace::SPtr MvcModelWorkspaces::getWorkspace (const std::string& aName)
{
	auto found {m_workspaces.find(aName)};

	if (found == m_workspaces.end()) return nullptr;

	return found->second;
}
// -----------------------------------------------------------------------------
Workspace::SPtr MvcModelWorkspaces::addWorkspace (const std::string& aName, jkpp::Git::UPtr&& aGit, const fs::path& aPath)
{
	if (aName.empty()) return nullptr;
    if (m_workspaces.find(aName) != m_workspaces.end()) return nullptr;

    beginUpdate();
    Workspace::SPtr ws {std::make_shared<Workspace>(aName, std::move(aGit), aPath)};
    m_workspaces.insert(std::make_pair(aName, ws));
    endUpdate();

    return ws;
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::removeWorkspace (const std::string& aName)
{
	auto found {m_workspaces.find(aName)};
    if (m_workspaces.find(aName) == m_workspaces.end()) return false;

    beginUpdate();

	m_workspaces.erase(found);

    endUpdate();

    return true;
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::load (jkpp::GitBuilder& aGitBuilder)
{
    m_workspaces.clear();
	if (!fs::exists(m_workspacesDirPath)) return false;

    fs::directory_iterator dir { m_workspacesDirPath };

    for (;dir != fs::directory_iterator(); ++dir) {
        if ( (fs::is_directory(dir->path()))
		     && (dir->path().extension() == ".git") ) {
        	jkpp::Git::UPtr git {aGitBuilder.create()};
            git->set(dir->path().string());
			if (!addWorkspace(dir->path().stem().string(), std::move(git))) return false;
        }
    }

    std::ifstream file {m_confFilePath.string(), std::fstream::in};
    if (!file) return false;

    beginUpdate();
    bool result {loadLines (file, aGitBuilder)};
    endUpdate();

	return result;
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::save ()
{
    std::ofstream file {m_confFilePath.string(), std::fstream::out};
    if (!file) return false;

    for (auto ws : m_workspaces) {
    	if (!ws.second->getPath().empty())
	    	file << "workspace=" << ws.first << ':' << ws.second->getPath().string() << '\n';
    }
	return  true;
}
// -----------------------------------------------------------------------------
bool MvcModelWorkspaces::loadLines (std::ifstream& aFile, jkpp::GitBuilder& aGitBuilder)
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
            fs::path path {value.substr(ws_pos + 1)};
			if (!fs::exists(path)) continue;

            auto ws {m_workspaces.find(name)};
            if (ws == m_workspaces.end()) return false;

			ws->second->setPath(path);

		    fs::directory_iterator dir {path};

		    for (;dir != fs::directory_iterator(); ++dir) {
		        if ( fs::is_directory(dir->path())
				     && fs::exists(dir->path() / "project.conf") ) {
					if (!ws->second->addProject(dir->path().filename().string())) return false;
		        }
		    }
        }
        else return false;
    }
    return aFile.eof();
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
