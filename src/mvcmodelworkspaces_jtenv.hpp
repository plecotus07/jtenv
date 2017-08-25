// +++ -------------------------------------------------------------------------
#ifndef MVCMODELWORKSPACES_JTENV_HPP
#define MVCMODELWORKSPACES_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"

#include <mvcmodelimpl_jkpp.hpp>

#include <boost/filesystem.hpp>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelWorkspaces : public jkpp::MvcModelImpl {
	public:
		MvcModelWorkspaces ();

		const fs::path& getConfFilePath () const { return m_confFilePath; }
		const fs::path& getWorkspacesDirPath () const { return m_workspacesDirPath; }

		Item::SPtr      getItem (const std::string& aWsName, const std::string& aProjName);
		Workspace::SPtr getWorkspace (const std::string& aName);
		Workspace::SPtr addWorkspace (const std::string& aName, jkpp::Git::UPtr&& aGit, const fs::path& aPath = fs::path());
        bool            removeWorkspace (const std::string& aName);

		bool load (jkpp::GitBuilder& aGitBuilder);
		bool save ();

        const Workspace::SPtrByStrMap& getWorkspaces () const { return m_workspaces; }

        Workspace::Iterator begin () { return m_workspaces.begin(); };
        Workspace::Iterator end () { return m_workspaces.end(); };

	protected:
		Workspace::SPtrByStrMap m_workspaces;

		const fs::path m_confFilePath;
		const fs::path m_workspacesDirPath;

		bool loadLines (std::ifstream& aFile, jkpp::GitBuilder& aGitBuilder);
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELWORKSPACES_JTENV_HPP
// +++ -------------------------------------------------------------------------
