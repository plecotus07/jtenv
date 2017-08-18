// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLMAIN_JTENV_HPP
#define MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
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
// +++ -------------------------------------------------------------------------
class MvcCtrlMain {
	public:
		MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, jkpp::GitBuilder& aGitBuilder);

		bool loadConfig ();
		bool saveConfig ();

        bool setUserName (const std::string& aUserName);
        bool setUserEmail (const std::string& aUserEmail);

        bool initWorkspace (const std::string& aName, const fs::path& aPath);
        bool initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, bool clone);

	protected:
		MvcModelConfig&     m_configModel;
		MvcModelWorkspaces& m_workspacesModel;
        jkpp::GitBuilder&          m_gitBuilder;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
