// +++ -------------------------------------------------------------------------
#include "mvcctrlmain_jtenv.hpp"

#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelproject_jtenv.hpp"
#include "mvcmodelworkspace_jtenv.hpp"
#include "projectconf_jtenv.hpp"

#include <git_jkpp.hpp>
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlMain::MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, MvcModelWorkspace& aWsModel, MvcModelProject& aProjModel, jkpp::GitBuilder& aGitBuilder) :
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel},
    m_wsModel {aWsModel},
    m_projModel {aProjModel},
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
void MvcCtrlMain::selectProject (Project::SPtr aProject)
{
    m_wsModel.setWorkspace(nullptr);
    m_projModel.setProject(aProject);
}
// -----------------------------------------------------------------------------
void MvcCtrlMain::selectWorkspace (Workspace::SPtr aWorkspace)
{
    m_projModel.setProject(nullptr);
    m_wsModel.setWorkspace(aWorkspace);
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initWorkspace (const std::string& aName, const fs::path& aPath)
{
    if (m_workspacesModel.getWorkspace(aName)) return false;

	jkpp::Git::UPtr git {m_gitBuilder.create()};

    if (!git->init((m_workspacesModel.getWorkspacesDirPath() / (aName + ".git")).string(), true)) return false;

	Workspace::SPtr ws {m_workspacesModel.addWorkspace(aName, std::move(git))};
    if (!ws) return false;

    if (!ws->clone(m_configModel.getUserName(), m_configModel.getUserEmail(), aPath)) return false;

	if (!m_workspacesModel.save()) return false;

    try {
    	fs::copy(getConfDirPath() / "gitignore.tmpl", ws->getPath() / ".gitignore");
    } catch (...) {
    	return false;
    }

	if (!ws->git("add .")) return false;
    if (!ws->git("commit -m\"Initialize repo.\"")) return false;
    if (!ws->git("push -u origin master")) return false;

	return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initProject (const std::string& aWsName, const std::string& aName, const std::string& aFullName, const std::string& aRepoUrl, bool aClone)
{
	Workspace::SPtr ws {m_workspacesModel.getWorkspace(aWsName)};
    if (!ws) return false;

    Project::SPtr proj {ws->addProject(aName)};
    if (!proj) return false;

    if (!proj->init(aFullName, m_gitBuilder.create(aRepoUrl))) return false;

    if (aClone && !proj->clone(m_configModel.getUserName(), m_configModel.getUserEmail())) return false;

	return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::cloneItem (const fs::path& aPath)
{
	MvcModelItem* model {};
    if (m_wsModel.getWorkspace()) model = &m_wsModel;
    else if (m_projModel.getProject()) model = &m_projModel;
    if (!model) return false;

	if (!model->clone(m_configModel.getUserName(), m_configModel.getUserEmail(), aPath)) return false;

    return m_workspacesModel.save();
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::clearItem (bool aForce, std::string& aDetails)
{
	MvcModelItem* model;
    if (m_wsModel.getWorkspace()) model = &m_wsModel;
    else if (m_projModel.getProject()) model = &m_projModel;
    if (!model) return false;

    bool result {true};
	if (!model->clear(aForce, aDetails)) result = false;
    if (!m_workspacesModel.save()) result = false;

    return result;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::git (const std::string& aGitCmd)
{
	MvcModelItem* model;
    if (m_wsModel.getWorkspace()) model = &m_wsModel;
    else if (m_projModel.getProject()) model = &m_projModel;
    if (!model) return false;

    return model->git(aGitCmd);
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::cmakeAdd (const std::string& aName, const std::string& aCommand)
{
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::cmakeRemove (const std::string& aName)
{
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::cmakeExecute (const std::string& aCmdName)
{
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
