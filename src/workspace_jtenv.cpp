// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Workspace::Workspace (const std::string& aName, jkpp::Git::UPtr&& aGit, const fs::path& aPath) :
	m_name{aName},
    m_path{aPath},
    m_git{std::move(aGit)}
{
///\todo assert(m_git)
}
// -----------------------------------------------------------------------------
bool Workspace::clone (const std::string& aUserName, const std::string& aUserEmail)
{
	if (!m_git) return false;
    if (m_path.empty()) return false;

	jkpp::Git::UPtr clonedGit {m_git->clone(m_path.string(), false)};
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
Project::SPtr Workspace::initProject (const std::string& aName, jkpp::GitBuilder& aGitBuilder, const std::string& aFullName, const std::string& aRepoUrl)
{
	if (aName.empty()) return nullptr;
    if (m_path.empty()) return nullptr;
    if (m_projects.find(aName) != m_projects.end()) return nullptr;

    Project::SPtr proj {std::make_shared<Project>(m_name, aName, m_path / aName)};

    if (!proj->init(aFullName, aRepoUrl, aGitBuilder)) return nullptr;

	m_projects.insert(std::make_pair(aName, proj));

    return proj;
}
// -----------------------------------------------------------------------------
Project::SPtr Workspace::addProject (const std::string& aName)
{
	if (aName.empty()) return nullptr;
    if (m_path.empty()) return nullptr;
    if (m_projects.find(aName) != m_projects.end()) return nullptr;

    Project::SPtr proj {std::make_shared<Project>(m_name, aName, m_path / aName)};
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
