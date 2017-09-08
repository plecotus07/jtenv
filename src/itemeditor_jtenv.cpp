// +++ -------------------------------------------------------------------------
#include "itemeditor_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ItemEditor::ItemEditor (MvcModelProjectEdit& m_projModel, MvcViewProject& aProjView, MvcViewWorkspace& aWsView, MvcCtrlMain& aMainCtrl) :
    m_projView(aProjView),
    m_wsView(aWsView),
    m_mainCtrl(aMainCtrl)
{
}
// -----------------------------------------------------------------------------
void ItemEditor::Visit (Project* aProj)
{
}
// -----------------------------------------------------------------------------
void ItemEditor::Visit (Workspace* aWs)
{
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
