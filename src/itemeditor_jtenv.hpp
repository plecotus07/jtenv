// +++ -------------------------------------------------------------------------
#ifndef ITEMEDITOR_JTENV_HPP
#define ITEMEDITOR_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class ItemEditor: public ItemVisitor {
	public:
    	ItemVisitor (MvcViewProject& aProjView, MvcViewWorkspace& aWsView, MvcCtrlMain& aMainCtrl);

		virtual void Visit (Workspace* aWs);
		virtual void Visit (Project* aProj);

    private:
        MvcViewProject&   m_projView;
        MvcViewWorkspace& m_wsView;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEMEDITOR_JTENV_HPP
// +++ -------------------------------------------------------------------------
