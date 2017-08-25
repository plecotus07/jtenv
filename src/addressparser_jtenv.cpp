// +++ -------------------------------------------------------------------------
#include "addressparser_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
AddressParser::AddressParser (const Workspace::SPtrByStrMap& aWorkspaces) :
    m_workspaces {aWorkspaces}
{
}
// -----------------------------------------------------------------------------
std::pair<std::string, std::string> AddressParser::operator () (const std::string& aAddr, const fs::path& aPath)
{
	auto pos {aAddr.find_first_of(':')};

	std::string proj_name {};
	std::string ws_name {};

    fs::path path {aPath};

	if (pos == std::string::npos) {
    	ws_name = aAddr;
    } else {
		ws_name = aAddr.substr(0, pos);
		proj_name = aAddr.substr(pos + 1);
	}

    if (ws_name.empty() && proj_name.empty()) {
        for (bool eol = false; !path.empty() && !eol; path = path.parent_path()) {
            if ( fs::exists(path / "project.conf")
                     && (m_workspaces.find(path.parent_path().filename().string()) != m_workspaces.end()) ) {
                ws_name = path.parent_path().filename().string();
                proj_name = path.filename().string();
                eol = true;
            } else if (auto found {m_workspaces.find(path.filename().string())};
                       (found != m_workspaces.end())
                       && (found->second->getPath() == path) ) {
                ws_name = path.filename().string();
                eol = true;
            }
        }
    } else if (ws_name.empty()) {
        for (; !path.empty() && !fs::exists(path / proj_name / "project.conf"); path = path.parent_path());

        if (!path.empty()
                && (m_workspaces.find(path.filename().string()) != m_workspaces.end()) ) ws_name = path.filename().string();
        else proj_name.clear();
    }

    return std::make_pair(ws_name, proj_name);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
