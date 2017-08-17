// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Workspace::Workspace (const std::string& aName, const fs::path& aPath) :
	m_name{aName},
    m_path{aPath}
{
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
