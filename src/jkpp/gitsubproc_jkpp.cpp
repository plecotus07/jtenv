// +++ -------------------------------------------------------------------------
#include "gitsubproc_jkpp.hpp"

#include "filesystem_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jkpp {
// +++ -------------------------------------------------------------------------
GitSubProc::GitSubProc () :
    m_path{}
{
}
// -----------------------------------------------------------------------------
bool GitSubProc::init (const std::string& aPath, bool aBare)
{
    if (!executeCommand("git init " + aPath + (aBare ? " --bare" : ""))) return false;

    m_path = aPath;

    return true;
}
// -----------------------------------------------------------------------------
Git::UPtr GitSubProc::clone (const std::string& aPath, bool aBare)
{
    if (!executeCommand("git clone " + m_path + " " + aPath + (aBare ? " --bare" : "") )) return nullptr;

    Git::UPtr result {std::make_unique<GitSubProc>()};

    result->set(aPath);

    return result;
}
// -----------------------------------------------------------------------------
bool GitSubProc::command (const std::string& aCommand) const
{
	return executeCommand("git -C " + m_path + " " + aCommand);
}
// +++ -------------------------------------------------------------------------
Git::UPtr GitSubProcBuilder::create () const
{
    return std::make_unique<GitSubProc>();
}
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
