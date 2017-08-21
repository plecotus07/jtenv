// +++ -------------------------------------------------------------------------
#include "mvcctrlmain_jtenv.hpp"

#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "projectconf_jtenv.hpp"

#include <git_jkpp.hpp>
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlMain::MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, jkpp::GitBuilder& aGitBuilder) :
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel},
    m_gitBuilder {aGitBuilder}
{
///\todo assert (m_git != nullptr)
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::loadConfig ()
{
    if ( (!fs::exists(m_configModel.getConfFilePath()))
         && (!saveConfig())) return false;

    if ( (!m_configModel.load())
         || (!m_workspacesModel.load()) ) return false;

    return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::saveConfig ()
{
    if (!fs::exists(getConfDirPath())) {
        try {
            fs::create_directories(getConfDirPath());
        } catch (fs::filesystem_error& e) {
            return false;
        }

        std::ofstream f {(getConfDirPath() / "gitignore.tmpl").string().c_str(), std::fstream::out};
        if (!f) return false;

        f << "*.bat\n"
             "_*\n"
             "build/\n"
             "tmp/\n";

        f.close();
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
	Workspace::SPtr ws {m_workspacesModel.getWorkspace(aName)};
    if (ws) return false;

    jkpp::Git::UPtr git_remote {m_gitBuilder.create()};

    if (!git_remote->init((m_workspacesModel.getWorkspacesDirPath() / (aName + ".git")).string(), true)) return false;

	jkpp::Git::UPtr git_local {git_remote->clone((aPath / aName).string(), false)};

    if (!git_local->command("config user.name \"" + m_configModel.getUserName() + "\"")) return false;
    if (!git_local->command("config user.email \"" + m_configModel.getUserEmail() + "\"")) return false;

    try {
    	fs::copy(getConfDirPath() / "gitignore.tmpl", aPath / aName / ".gitignore");
    } catch (...) {
    	return false;
    }

	if (!git_local->command("add .")) return false;
    if (!git_local->command("commit -m\"Initialize repo\"")) return false;
    if (!git_local->command("push -u origin master")) return false;

    m_workspacesModel.addWorkspace(aName, aPath/aName);

	if (!m_workspacesModel.save()) return false;

    return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, bool aClone)
{
	std::cerr << "+++ init project\n";
    std::cerr << "   ws name: " << aWsName << '\n';
    std::cerr << "   name: " << aName << '\n';
    std::cerr << "   full name: " << aFullName << '\n';
    std::cerr << "   clone: " << (aClone ? "true" : "false") << '\n';

	return false;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
