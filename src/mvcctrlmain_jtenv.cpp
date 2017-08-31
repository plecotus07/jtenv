// +++ -------------------------------------------------------------------------
#include "mvcctrlmain_jtenv.hpp"

#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelitem_jtenv.hpp"
#include "projectconf_jtenv.hpp"

#include <git_jkpp.hpp>
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlMain::MvcCtrlMain (MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, MvcModelItem& aItemModel, jkpp::GitBuilder& aGitBuilder) :
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel},
    m_itemModel {aItemModel},
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
void MvcCtrlMain::selectItem (Item::SPtr aItem)
{
    std::cerr << "+++: ctrl select: " << (aItem ? aItem->getName() : "null") << '\n';
    m_itemModel.setItem(aItem);
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::initWorkspace (const std::string& aName, const fs::path& aPath)
{
    if (m_workspacesModel.getWorkspace(aName)) return false;

	jkpp::Git::UPtr git {m_gitBuilder.create()};

    if (!git->init((m_workspacesModel.getWorkspacesDirPath() / (aName + ".git")).string(), true)) return false;

	Workspace::SPtr ws {m_workspacesModel.addWorkspace(aName, std::move(git))};
    if (!ws) return false;

    if (!ws->clone(aPath, m_configModel.getUserName(), m_configModel.getUserEmail())) return false;

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

    if (aClone && !proj->clone(ws->getPath() / aName, m_configModel.getUserName(), m_configModel.getUserEmail())) return false;

	return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::cloneWorkspace (const std::string& aName, const fs::path& aPath)
{
    Workspace::SPtr ws {m_workspacesModel.getWorkspace(aName)};

    if (!ws) return false;
	if (!ws->getPath().empty()) return false;
    if (fs::exists(aPath / aName)) return false;

    return ws->clone(aPath, m_configModel.getUserName(), m_configModel.getUserEmail());
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::cloneProject (const std::string& aWsName, const std::string& aName)
{
    Workspace::SPtr ws {m_workspacesModel.getWorkspace(aWsName)};
    if (!ws) return false;
	if (ws->getPath().empty()) return false;

    Project::SPtr proj {ws->getProject(aName)};
    if (!proj) return false;
    if (!fs::exists(proj->getPath())) return false;

    fs::path path {proj->getPath() / (aName + "_repo")};

    if (fs::exists(path)) return false;

    return proj->clone(path, m_configModel.getUserName(), m_configModel.getUserEmail());
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::clearWorkspace (const std::string& aName, std::string& aDetails, bool aForce)
{
    Workspace::SPtr ws {m_workspacesModel.getWorkspace(aName)};
    if (!ws) return false;
	if (!fs::exists(ws->getPath())) return false;

    jkpp::Git::Status status = ws->getStatus(aDetails);
	bool ws_edited {(status != jkpp::Git::Status::clean)
                    && (status != jkpp::Git::Status::empty)};

    bool projs_edited {false};
    std::string projs_details {};

	if (!aForce) {
        for (auto proj : *ws) {
            std::string proj_details {};
            auto proj_status {proj.second->getStatus(proj_details)};
            if ( (proj_status != jkpp::Git::Status::not_cloned)
            	     && (proj_status != jkpp::Git::Status::clean)
                     && (proj_status != jkpp::Git::Status::empty) ) {
				projs_details += proj.second->getName() + '\n' + proj_details + '\n';
				projs_edited = true;
            }
        }

        aDetails += (aDetails.empty() ? "" : "\n") + projs_details;

        if ( projs_edited
             || ws_edited ) return false;

	    aDetails.clear();
    }

    try { fs::remove_all(ws->getRepoPath()); } catch (...) { return false; }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::clearProject (const std::string& aWsName, const std::string& aName, std::string& aDetails, bool aForce)
{
    Workspace::SPtr ws {m_workspacesModel.getWorkspace(aWsName)};
    if (!ws) return false;
	if (!fs::exists(ws->getPath())) return false;

    Project::SPtr proj {ws->getProject(aName)};
    if (!proj) return false;
    if (!fs::exists(proj->getPath())) return false;
    if (!fs::exists(proj->getRepoPath())) return false;

    auto status {proj->getStatus(aDetails)};

    if (status != jkpp::Git::Status::clean
        && status != jkpp::Git::Status::empty
        && !aForce) return false;

    aDetails.clear();

    try { fs::remove_all(proj->getRepoPath()); } catch (...) { return false; }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcCtrlMain::git (const std::string& aWsName, const std::string& aProjName, const std::string& aGitCmd)
{
    Item::SPtr item {m_workspacesModel.getItem(aWsName, aProjName)};
    if (!item) return false;

    return item->git(aGitCmd);
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
