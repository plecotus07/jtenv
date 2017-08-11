// +++ -------------------------------------------------------------------------
#include "workspaces_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Workspaces::Workspaces (const Config::UPtr& aConfig, const jkpp::GitBuilder& aGitBuilder) :
    m_config(aConfig),
    m_gitBuilder(aGitBuilder)
{
///\todo assert(m_config.get() != nullptr)
}
// -----------------------------------------------------------------------------
Workspace::SPtr Workspaces::getWorkspace (const std::string& aName)
{
	auto found {m_workspaces.find(aName)};

	if (found == m_worspaces.end()) return nullptr;

	return found->second.get();
}
bool Workspaces::initWorkspace (const std::string& aName, const fs::path& aLocalDirPath)
{
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
