// +++ -------------------------------------------------------------------------
#ifndef MVCMODELWORKSPACES_JTENV_HPP
#define MVCMODELWORKSPACES_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"
#include <mvcmodelimpl_jkpp.hpp>

#include <boost/filesystem.hpp>
#include <map>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelWorkspaces : public jkpp::MvcModelImpl {
	public:
		using WorkspaceByStringMap = std::map<std::string, Workspace::SPtr>;
        using iterator = WorkspaceByStringMap::iterator;

		MvcModelWorkspaces ();

		const std::string& getConfFilePath () const { return m_confFilePath; }
		const fs::path&    getWorkspacesDirPath () const { return m_workspacesDirPath; }

		Workspace::SPtr getWorkspace (const std::string& aName);
		Workspace::SPtr addWorkspace (const std::string& aName, const fs::path& aPath = fs::path());

		bool load ();
		bool save ();

		bool clean ();

        iterator begin () { return m_workspaces.begin(); };
        iterator end () { return m_workspaces.end(); };

	protected:
		WorkspaceByStringMap m_workspaces;

		const std::string m_confFilePath;
		const fs::path    m_workspacesDirPath;

		bool loadLines (std::ifstream& aFile);

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELWORKSPACES_JTENV_HPP
// +++ -------------------------------------------------------------------------
