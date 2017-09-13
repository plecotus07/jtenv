// +++ -------------------------------------------------------------------------
#include "mvcctrlprojectedit_jtenv.hpp"
#include "project_jtenv.hpp"
#include "mvcmodelprojectedit_jtenv.hpp"
#include "mvcmodelitemselection_jtenv.hpp"
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
    m_editModel.endUpdate();
}
// -----------------------------------------------------------------------------
bool MvcCtrlProjectEdit::submitEdit ()
{
	if (!m_project) return false;

	std::string old_fullname {m_project->getFullName()};
    std::string old_remote_url {m_project->getRemoteRepoUrl()};

    m_itemSelModel.beginUpdate();
    m_project->setFullName(m_editModel.getFullName());
    m_project->setRemoteRepoUrl(m_editModel.getRemoteRepoUrl());

    bool result {true};
    if (!m_project->save()) {
    	m_project->setFullName(old_fullname);
        m_project->setRemoteRepoUrl(old_remote_url);
        result = false;
    }

    m_itemSelModel.endUpdate();
    return result;

}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
