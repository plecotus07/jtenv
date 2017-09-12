// +++ -------------------------------------------------------------------------
#include "mvceditorcliitem_jtenv.hpp"
#include "mvcmodelitemselection_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcEditorCliItem::MvcEditorCliItem(jkpp::MvcViewCli::ArgIterator& aArg, const jkpp::MvcViewCli::ArgIterator& aArgsEnd, MvcModelItemSelection& aItemSelModel) :
    m_itemSelModel {aItemSelModel},
    m_projModel {},
    m_projCtrl {m_projModel, m_itemSelModel},
    m_projView {aArg, aArgsEnd, m_projCtrl, m_projModel}
{
}
// -----------------------------------------------------------------------------
bool MvcEditorCliItem::edit ()
{
	ItemVisitorEdit visitor {m_projView, m_projCtrl};
	m_itemSelModel.getItem()->accept(visitor);

	return visitor;
}
// +++ -------------------------------------------------------------------------
bool MvcEditorCliItem::containsCommand (const std::string& aCmd)
{
	ItemVisitorContainsCommand visitor {aCmd, m_projView};
	m_itemSelModel.getItem()->accept(visitor);

	return visitor;
}
// +++ -------------------------------------------------------------------------
ItemVisitorEdit::ItemVisitorEdit (MvcViewCliProject& aProjView, MvcCtrlProjectEdit& aProjCtrl) :
	m_projCtrl {aProjCtrl},
    m_projView {aProjView},
    m_result {true}
{
}
// -----------------------------------------------------------------------------
void ItemVisitorEdit::Visit (Workspace*)
{
}
// -----------------------------------------------------------------------------
void ItemVisitorEdit::Visit (Project* aProject)
{
    m_projCtrl.prepareEdit(aProject);

    m_projView.show();

    if (!m_projView.getResult()) {
    	m_result = false;
        return;
    }
    if (!m_projView.submitEdit()) {
    	m_result = false;
    }
}
// +++ -------------------------------------------------------------------------
ItemVisitorContainsCommand::ItemVisitorContainsCommand (const std::string& aCmd, MvcViewCliProject& aProjView) :
    m_cmd {aCmd},
    m_projView {aProjView},
    m_result {true}
{
}
// -----------------------------------------------------------------------------
void ItemVisitorContainsCommand::Visit (Workspace*)
{
}
// -----------------------------------------------------------------------------
void ItemVisitorContainsCommand::Visit (Project*)
{
	m_result = m_projView.containsCommand(m_cmd);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
