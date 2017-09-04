// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLMAIN_JTENV_HPP
#define MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"

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
class MvcModelItem;
// +++ -------------------------------------------------------------------------
class MvcCtrlMain {
	public:
		MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, MvcModelItem& aItemModel, jkpp::GitBuilder& aGitBuilder);

		bool loadConfig ();
		bool saveConfig ();

        bool setUserName (const std::string& aUserName);
        bool setUserEmail (const std::string& aUserEmail);

		void selectItem (Item::SPtr aItem);

        bool initWorkspace (const std::string& aName, const fs::path& aPath);
        bool initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, const std::string& aRepoUrl, bool clone);

		bool cloneItem (const fs::path& aPath);

		bool cloneWorkspace (const std::string& aName, const fs::path& aPath);
        bool cloneProject (const std::string& aWsName, const std::string& aName);

		bool clearItem (bool aForce, std::string& aDetails);

		bool git (const std::string& aGitCmd);

		bool cmakeAdd (const std::string& aName, const std::string& aCommand);
		bool cmakeRemove (const std::string& aName);
		bool cmakeExecute (const std::string& aCmdName);

	protected:
		MvcModelConfig&     m_configModel;
		MvcModelWorkspaces& m_workspacesModel;
		MvcModelItem&       m_itemModel;
        jkpp::GitBuilder&   m_gitBuilder;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
