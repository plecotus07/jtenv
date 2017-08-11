// +++ -------------------------------------------------------------------------
#include "mvcctrlmain_jtenv.hpp"

#include "mvcmodelconfig_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlMain::MvcCtrlMain (MvcModelConfig& aConfigModel) :
    m_configModel {aConfigModel}
{
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::loadConfig ()
{
    return m_configModel.load();
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::setUserName (const std::string& aUserName)
{
    return m_configModel.setUserName(aUserName);
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::setUserEmail (const std::string& aUserEmail)
{
    return m_configModel.setUserEmail(aUserEmail);
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::setWorkspacesDirPath (const fs::path& aWorkspacesDirPath)
{
    return m_configModel.setWorkspacesDirPath(aWorkspacesDirPath);
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initWorkspace (const std::string& aName)
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
