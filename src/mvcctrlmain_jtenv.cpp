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
         && (!m_configModel.save())) return false;

    if (m_configModel.load()) return false;

    if ( (!fs::exists(m_workspacesModel.getConfFilePath()))
         && (!m_workspacesModel.save())) return false;

    if (m_workspacesModel.load()) return false;

    return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::saveConfig ()
{
    return (m_configModel.save()
            && m_workspaces.save());
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
bool MvcCtrlMain::setWorkspacesDirPath (const fs::path& aWorkspacesDirPath)
{
    m_configModel.setWorkspacesDirPath(aWorkspacesDirPath);
    return saveConfig();
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initWorkspace (const std::string& aName, const std::path& aPath)
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
