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
		MvcModelWorkspaces ();

		const std::string& getConfFilePath () const { return m_confFilePath; }
		const fs::path&    getWorkspacesDirPath () const { return m_workspacesDirPath; }

		Item::SPtr      getItem (const std::string& aAddr, const fs::path& aPath);
		Workspace::SPtr getWorkspace (const std::string& aName);
		Workspace::SPtr addWorkspace (const std::string& aName, const fs::path& aPath = fs::path());

		bool load ();
		bool save ();

        Workspace::Iterator begin () { return m_workspaces.begin(); };
        Workspace::Iterator end () { return m_workspaces.end(); };

	protected:
		Workspace::SPtrByStrMap m_workspaces;

		const std::string m_confFilePath;
		const fs::path    m_workspacesDirPath;

		bool loadLines (std::ifstream& aFile);

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELWORKSPACES_JTENV_HPP
// +++ -------------------------------------------------------------------------
