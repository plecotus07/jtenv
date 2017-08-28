// +++ -------------------------------------------------------------------------
#include "gitsubproc_jkpp.hpp"

#include "filesystem_jkpp.hpp"
#include <sstream>
#include <regex>
#include <iostream>
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
// -----------------------------------------------------------------------------
Git::Status GitSubProc::getStatus (std::string& aStatusDetails) const
{
    std::string workcopy {};
    if (!executeCommand("git -C " + m_path + " status -s", workcopy)) return Status::unknown;

    if (!workcopy.empty()) {
    	aStatusDetails = workcopy;
        return Status::not_commited;
    }

	std::string branchesStr {};
    if (!executeCommand("git -C " + m_path + " branch", branchesStr)) return Status::unknown;
    if (branchesStr.empty()) return Status::empty;

    std::list<std::string> branches;
    std::stringstream ss {branchesStr};
    std::string currentBranch {};

    for (std::string branch; std::getline(ss, branch);) {
        if (branch[0] == '*') currentBranch = branch.substr(2);
        else branches.push_back(branch.substr(2));
    }
    branches.push_front(currentBranch);

    bool not_pushed {false};

    for (auto branch : branches) {
        if ( (branch != currentBranch)
        	 && (!executeCommand("git -C " + m_path + " checkout -q " + branch)) ) return Status::unknown;

		std::string branchStatus {};
        if (!executeCommand("git -C " + m_path + " status -sb", branchStatus)) return Status::unknown;

	    std::regex pattern {R"(## ([^\.]+)(\.\.\.)?([^\s]*)? ?(\[.*\])?)"};

        std::smatch matches;
        if (!std::regex_search(branchStatus, matches, pattern)) return Status::unknown;

        bool branch_local_only {matches[3] == ""};
        bool branch_not_pushed {matches[4] != ""};

		if ( (branch_local_only)
                 || (branch_not_pushed) ) {
			aStatusDetails = branchStatus;
            not_pushed = true;
            break;
        }
    }
	if (!executeCommand("git -C " + m_path + " checkout -q " + currentBranch)) return Status::unknown;

	if (not_pushed) return Status::not_pushed;

	return Status::clean;
}
// +++ -------------------------------------------------------------------------
Git::UPtr GitSubProcBuilder::create () const
{
    return std::make_unique<GitSubProc>();
}
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
