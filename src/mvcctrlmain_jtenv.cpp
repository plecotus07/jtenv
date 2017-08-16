// +++ -------------------------------------------------------------------------
#include "mvcctrlmain_jtenv.hpp"

#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlMain::MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel) :
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel}
{
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::loadConfig ()
{
    if ( (!fs::exists(m_configModel.getConfFilePath()))
         && (!saveConfig())) return false;

    if ( (!m_configModel.load())
         || (!m_workspacesModel.load()) ) return false;

	if (m_workspacesModel.clean()) saveConfig();

    return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::saveConfig ()
{
    if (!fs::exists(fs::path(m_configModel.getConfFilePath()).parent_path())) {
        try {
            fs::create_directories(fs::path(m_configModel.getConfFilePath()).parent_path());
        } catch (fs::filesystem_error& e) {
            return false;
        }
    }

    if (!fs::exists(m_workspacesModel.getWorkspacesDirPath())) {
		try {
        	fs::create_directories(m_workspacesModel.getWorkspacesDirPath());
        } catch (fs::filesystem_error& e) {
        	return false;
        }
    }

    return (m_configModel.save()
            && m_workspacesModel.save());
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::setUserName (const std::string& aUserName)
{
    m_configModel.setUserName(aUserName);

    return saveConfig();
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::setUserEmail (const std::string& aUserEmail)
{
    m_configModel.setUserEmail(aUserEmail);
    return saveConfig();
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initWorkspace (const std::string& aName, const fs::path& aPath)
{
	return false;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, bool aClone)
{
	return false;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
