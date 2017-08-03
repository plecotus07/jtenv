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
bool MvcCtrlMain::setWorkspacesUrl (const std::string& aWorkspacesUrl)
{
    return m_configModel.setWorkspacesUrl(aWorkspacesUrl);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
