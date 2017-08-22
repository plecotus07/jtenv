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
         || (!m_workspacesModel.load(m_gitBuilder)) ) return false;

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

        std::ofstream f {(getConfDirPath() / "gitignore.tmpl").string(), std::fstream::out};
        if (!f) return false;

        f << "*_repo/\n"
		     "*.bat\n"
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
    if (m_workspacesModel.getWorkspace(aName)) return false;

	jkpp::Git::UPtr git {m_gitBuilder.create()};

    if (!git->init((m_workspacesModel.getWorkspacesDirPath() / (aName + ".git")).string(), true)) return false;

	Workspace::SPtr ws {m_workspacesModel.addWorkspace(aName, std::move(git), aPath / aName)};
    if (!ws) return false;
	if (!m_workspacesModel.save()) return false;

    if (!ws->clone(m_configModel.getUserName(), m_configModel.getUserEmail())) return false;

    try {
    	fs::copy(getConfDirPath() / "gitignore.tmpl", aPath / aName / ".gitignore");
    } catch (...) {
    	return false;
    }

	if (!ws->getGit().command("add .")) return false;
    if (!ws->getGit().command("commit -m\"Initialize repo.\"")) return false;
    if (!ws->getGit().command("push -u origin master")) return false;

	return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, const std::string& aRepoUrl, bool aClone)
{
	Workspace::SPtr ws {m_workspacesModel.getWorkspace(aWsName)};
    if (!ws) return false;

    Project::SPtr proj {ws->initProject(aName, m_gitBuilder, aFullName, aRepoUrl)};
    if (!proj) return false;

    if (aClone && !proj->clone(m_configModel.getUserName(), m_configModel.getUserEmail())) return false;

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
