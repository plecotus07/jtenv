// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLMAIN_JTENV_HPP
#define MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "project_jtenv.hpp"
#include "workspace_jtenv.hpp"

#include <boost/filesystem.hpp>
#include <string>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
// +++ -------------------------------------------------------------------------
namespace jkpp {
class GitBuilder;
}
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfig;
class MvcModelWorkspaces;
class MvcModelItemSelection;
// +++ -------------------------------------------------------------------------
class MvcCtrlMain {
	public:
		MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel,
		             MvcModelItemSelection& aItemSelModel, jkpp::GitBuilder& aGitBuilder);

		bool loadConfig ();
		bool saveConfig ();

        bool initWorkspace (const std::string& aName, const fs::path& aPath);
        bool initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, const std::string& aRepoUrl, bool clone);

		void selectItem (Item::SPtr aItem);
		bool cloneItem (const fs::path& aPath);
		bool clearItem (bool aForce, std::string& aDetails);
		bool git (const std::string& aGitCmd);

	protected:
		MvcModelConfig&        m_configModel;
		MvcModelWorkspaces&    m_workspacesModel;
		MvcModelItemSelection& m_itemSelModel;
        jkpp::GitBuilder&      m_gitBuilder;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
