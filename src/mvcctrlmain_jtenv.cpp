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
///\todo assert (aName.empty())
	if (aName.empty()) return false;

	const Config::UPtr& config {m_configModel.getConfig()};
///\todo assert(config != nullptr)
	if (config == nullptr) return false;

	fs::path wss_path {config->getWorkspacesDirPath()};

    if (wss_path.empty()) return false;
    if (!fs::exists(wss_path)) {
    	try {
	    	fs::create_directories(wss_path);
        } catch (...) {
        	return false;
        }
    }

    fs::path repo_path {wss_path / (aName + ".git")};

	if (fs::exists(repo_path)) return false;

    int result {std::system(("git init --bare " + repo_path.string()).c_str())};

	return (result == 0);
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, bool aClone)
{
	const Config::UPtr& config {m_configModel.getConfig()};
///\todo assert(config != nullptr)
	if (config == nullptr) return false;

///\todo assert (aName.empty())
	if (aName.empty()) return false;

    std::string ws_name {aWsName};
	if (aWsName.empty()) {
 //       ws_name =
    }

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
