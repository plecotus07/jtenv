// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Workspace::Workspace (const std::string& aName, jkpp::Git::UPtr&& aRemoteGit, jkpp::Git::UPtr&& aGit) :
	m_name{aName},
	m_remoteGit{std::move(aRemoteGit)},
	m_git{std::move(aGit)},
	m_projects{}

{
///\todo assert(m_remoteGit)
}
// -----------------------------------------------------------------------------
bool Workspace::clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path& aPath)
{
	if (!m_remoteGit) return false;
    if (m_git) return false;
    if (aPath.empty()) return false;

	fs::path ws_path {aPath / m_name};
    if (fs::exists(ws_path)) return false;

	jkpp::Git::UPtr clonedGit {m_remoteGit->clone(ws_path.string(), false)};
    if (!clonedGit) return false;

    m_git = std::move(clonedGit);

    m_git->command("config user.name \"" + aUserName + "\"");
    m_git->command("config user.email \"" + aUserEmail + "\"");

	return true;
}
// -----------------------------------------------------------------------------
bool Workspace::clear (bool aForce, std::string& aDetails)
{
	if (!fs::exists(getPath())) return false;

    jkpp::Git::Status status = getStatus(aDetails);
	bool ws_edited {(status != jkpp::Git::Status::clean)
                    && (status != jkpp::Git::Status::empty)};

    bool projs_edited {false};
    std::string projs_details {};

	if (!aForce) {
        for (auto proj : *this) {
            std::string proj_details {};
            auto proj_status {proj.second->getStatus(proj_details)};
            if ( (proj_status != jkpp::Git::Status::not_cloned)
            	     && (proj_status != jkpp::Git::Status::clean)
                     && (proj_status != jkpp::Git::Status::empty) ) {
				projs_details += proj.second->getName() + '\n' + proj_details + '\n';
				projs_edited = true;
            }
        }

        aDetails += (aDetails.empty() ? "" : "\n") + projs_details;

        if ( projs_edited
             || ws_edited ) return false;

	    aDetails.clear();
    }

    bool result {true};
    try { fs::remove_all(getRepoPath()); } catch (...) { result = false; }

	m_git.reset();

    return result;
}
// -----------------------------------------------------------------------------
bool Workspace::git (const std::string& aCommand)
{
	if (!m_git) return false;

    return m_git->command(aCommand);
}
// -----------------------------------------------------------------------------
jkpp::Git::Status Workspace::getStatus (std::string& aStatusDetails) const
{
	if ( (!m_git)
            || (!fs::exists(m_git->getUrl())) ) return jkpp::Git::Status::not_cloned;

    return m_git->getStatus(aStatusDetails);
}
// -----------------------------------------------------------------------------
Project::SPtr Workspace::addProject (const std::string& aName)
{
	if (aName.empty()) return nullptr;
	if (!m_git) return nullptr;
	if (!fs::exists(m_git->getUrl())) return nullptr;
    if (m_projects.find(aName) != m_projects.end()) return nullptr;

    Project::SPtr proj {std::make_shared<Project>(m_name, aName, fs::path{m_git->getUrl()} / aName)};
    m_projects.insert(std::make_pair(aName, proj));

	return proj;
}
// -----------------------------------------------------------------------------
Project::SPtr Workspace::getProject (const std::string& aName)
{
	auto found {m_projects.find(aName)};

	if (found == m_projects.end()) return nullptr;

	return found->second;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
