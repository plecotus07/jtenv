// +++ -------------------------------------------------------------------------
#ifndef WORKSPACE_JTENV_HPP
#define WORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <git_jkpp.hpp>

#include <boost/filesystem.hpp>
#include <memory>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class Workspace {
    public:
    	using SPtr = std::shared_ptr<Workspace>;

        Workspace (const std::string& aName, const fs::path& aPath, jkpp::Git::UPtr&& aGit);

    protected:
    	std::string    m_name;
        fs::path       m_path;
        jkpp::Git::UPtr m_git;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // WORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
