// +++ -------------------------------------------------------------------------
#include "gitsubproc_jkpp.hpp"

#include "filesystem_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jkpp {
// +++ -------------------------------------------------------------------------
GitSubProc::GitSubProc () :
    m_localPath{},
    m_remoteUrl{}
{
}
// -----------------------------------------------------------------------------
bool GitSubProc::init (const std::string& aPath, bool aBare)
{
    if (!executeCommand("git init " + aPath +  + (aBare ? " --bare" : ""))) return false;

    m_localPath = aPath;

    return true;
}
// -----------------------------------------------------------------------------
bool GitSubProc::clone (const std::string& aLocalPath, const std::string& aRemoteUrl, bool aBare)
{
    if (!executeCommand("git clone " + aRemoteUrl + " " + aLocalPath)) return false;
    m_remoteUrl = aRemoteUrl;
    m_localPath = aLocalPath;

}
// -----------------------------------------------------------------------------
bool GitSubProc::command (const std::string& aCommand) const
{
	return executeCommand("git -C " + m_localPath + " " + aCommand);
}
// -----------------------------------------------------------------------------
bool GitSubProc::set (const std::string& aPath)
{
	if (!fs::exists(aPath)) return false;

    if (!fs::exists(fs::path(aPath) / ".git")) return false;

    m_localPath = aPath;

	std::string output {};
    if (!executeCommand("git -C " + m_localPath + " remote get-url origin", output)) return false;

	m_remoteUrl = output;

    return true;
}
// +++ -------------------------------------------------------------------------
Git::UPtr GitSubProcBuilder::create () const
{
    return std::make_unique<GitSubProc>();
}
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
