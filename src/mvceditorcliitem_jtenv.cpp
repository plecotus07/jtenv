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
    m_projView {aArg, aArgsEnd, m_projCtrl, m_projModel},
    m_result {true}
{
}
// -----------------------------------------------------------------------------
bool MvcEditorCliItem::edit ()
{
	m_itemSelModel.getItem()->accept(*this);

	return m_result;
}
// -----------------------------------------------------------------------------
void MvcEditorCliItem::Visit (Workspace*)
{
}
// -----------------------------------------------------------------------------
void MvcEditorCliItem::Visit (Project* aProj)
{
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
} // jtenv
// +++ -------------------------------------------------------------------------
