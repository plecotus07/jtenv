// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Workspace::Workspace (const std::string& aName, jkpp::Git::UPtr&& aRemoteGit, jkpp::Git::UPtr&& aGit) :
	m_name{aName},
	m_remoteGit{std::move(aRemoteGit)},
	m_git{std::move(aGit)}
{
///\todo assert(m_remoteGit)
}
// -----------------------------------------------------------------------------
bool Workspace::clone (const fs::path& aPath, const std::string& aUserName, const std::string& aUserEmail)
{
	if (!m_remoteGit) return false;
    if (m_git) return false;
    if (aPath.empty()) return false;
    if (fs::exists(aPath)) return false;

	jkpp::Git::UPtr clonedGit {m_remoteGit->clone(aPath.string(), false)};
    if (!clonedGit) return false;

    m_git = std::move(clonedGit);

    m_git->command("config user.name \"" + aUserName + "\"");
    m_git->command("config user.email \"" + aUserEmail + "\"");

	return true;
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
