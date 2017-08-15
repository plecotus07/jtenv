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

		MvcModelWorkspaces ();

		Workspace::SPtr getWorkspace (const std::string& aName);
		Workspace::SPtr addWorkspace (const std::string& aName, const fs::path& aPath);

		bool load ();
		bool save ();

	protected:
		WorkspaceByStringMap m_workspaces;

		const std::string m_confFilePath;

		bool loadLines (std::ifstream& aFile);

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELWORKSPACES_JTENV_HPP
// +++ -------------------------------------------------------------------------
