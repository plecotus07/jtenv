// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLMAIN_JTENV_HPP
#define MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <string>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfig;
class MvcModelWorkspaces;
// +++ -------------------------------------------------------------------------
class MvcCtrlMain {
	public:
		MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel);

		bool loadConfig ();
		bool saveConfig ();
		
        bool setUserName (const std::string& aUserName);
        bool setUserEmail (const std::string& aUserEmail);
        bool setWorkspacesDirPath (const fs::path& aWorkspacesDirPath);

        bool initWorkspace (const std::string& aName);
        bool initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, bool clone);

	protected:
		MvcModelConfig&     m_configModel;
		MvcModelWorkspaces& m_workspacesModel;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
