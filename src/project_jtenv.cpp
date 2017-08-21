// +++ -------------------------------------------------------------------------
#include "project_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Project::Project (const std::string& aWsName, const std::string& aName, jkpp::Git::UPtr&& aGit, const fs::path& aPath) :
	m_wsName {aWsName},
	m_name{aName},
    m_path{aPath},
    m_git{std::move(aGit)}
{
}
// -----------------------------------------------------------------------------
bool Project::clone (const std::string& aUserName, const std::string& aUserEmail)
{
	return false;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
