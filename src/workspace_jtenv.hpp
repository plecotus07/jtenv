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

        Workspace (const std::string& aName, const fs::path& aPath);

        const std::string& getName () const { return m_name; }

        const fs::path&    getPath () const { return m_path; }
        void               setPath (const fs::path& aPath) { m_path = aPath; }

    protected:
    	std::string    m_name;
        fs::path       m_path;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // WORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
