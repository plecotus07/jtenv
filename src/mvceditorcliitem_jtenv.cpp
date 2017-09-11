// +++ -------------------------------------------------------------------------
#include "mvceditorcliconfig_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcEditorCliItem::MvcEditorCliItem(jkpp::MvcViewCli::ArgIterator& aArg, const jkpp::MvcViewCli::ArgIterator& aArgsEnd, MvcModelItemSelection& aItemModel) :
    m_itemModel {aItemModel}
    m_projModel {},
    m_projCtrl {m_projModel, m_itemModel},
    m_projView {aArg, aArgsEnd, m_projCtrl, m_projModel}
    m_result {true}
{
}
// -----------------------------------------------------------------------------
bool MvcEditorCliItem::edit ()
{
	Visit(m_itemModel.getItem());

	return m_result;
}
// -----------------------------------------------------------------------------
void MvcEditorCliItem::Visit (Workspace* aWs)
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
