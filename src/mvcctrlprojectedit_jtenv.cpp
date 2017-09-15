// +++ -------------------------------------------------------------------------
#include "mvcctrlprojectedit_jtenv.hpp"
#include "project_jtenv.hpp"
#include "mvcmodelprojectedit_jtenv.hpp"
#include "mvcmodelitemselection_jtenv.hpp"

#include <filesystem_jkpp.hpp>

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlProjectEdit::MvcCtrlProjectEdit (MvcModelProjectEdit& aEditModel, MvcModelItemSelection& aItemSelModel) :
    m_project {},
    m_editModel {aEditModel},
    m_itemSelModel {aItemSelModel}
{
}
// -----------------------------------------------------------------------------
void MvcCtrlProjectEdit::prepareEdit (Project* aProject)
{
	if (!aProject) return;
    m_project = aProject;

	m_editModel.beginUpdate();
    m_editModel.setFullName(aProject->getFullName());
    m_editModel.setRemoteRepoUrl(aProject->getRemoteRepoUrl());
    m_editModel.setDefaultBranch(aProject->getDefaultBranch());
	m_editModel.setCustomCmds(aProject->getCustomCmds());
    m_editModel.endUpdate();
}
// -----------------------------------------------------------------------------
bool MvcCtrlProjectEdit::submitEdit ()
{
	if (!m_project) return false;

	std::string old_fullname {m_project->getFullName()};
    std::string old_remote_url {m_project->getRemoteRepoUrl()};
    std::string old_default_branch {m_project->getDefaultBranch()};
	auto old_custom_cmds {m_project->getCustomCmds()};

    m_itemSelModel.beginUpdate();
    m_project->setFullName(m_editModel.getFullName());
    m_project->setRemoteRepoUrl(m_editModel.getRemoteRepoUrl());
    m_project->setDefaultBranch(m_editModel.getDefaultBranch());
    m_project->setCustomCmds(m_editModel.getCustomCmds());

    bool result {true};
    if (!m_project->save()) {
    	m_project->setFullName(old_fullname);
        m_project->setRemoteRepoUrl(old_remote_url);
        m_project->setDefaultBranch(old_default_branch);
        m_project->setCustomCmds(old_custom_cmds);
        result = false;
    }

    m_itemSelModel.endUpdate();

    return result;
}
// -----------------------------------------------------------------------------
bool MvcCtrlProjectEdit::executeCustomCmd (const std::string& aName)
{
	if (!m_project) return false;

	Project::CustomCmd cmd {m_editModel.getCustomCmd(aName)};
    if (cmd.second.empty()) return false;

    fs::path execute_path {m_project->getPath() / cmd.first};

    if (!fs::exists(execute_path)) {
    	try { fs::create_directories(execute_path); } catch (...) { return false; };
    }

	try { fs::current_path(execute_path); } catch (...) { return false; };

    return jkpp::executeCommand(cmd.second);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
