// +++ -------------------------------------------------------------------------
#ifndef MVCEDITORCLIITEM_JTENV_HPP
#define MVCEDITORCLIITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "mvcmodelprojectedit_jtenv.hpp"
#include "mvcctrlprojectedit_jtenv.hpp"
#include "mvcviewcliproject_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelItemSelection;
// +++ -------------------------------------------------------------------------
class MvcEditorCliItem : public ItemVisitor {
	public:
        MvcEditorCliItem (jkpp::MvcViewCli::ArgIterator& aArg, const jkpp::MvcViewCli::ArgIterator& aArgsEnd, MvcModelItemSelection& aItemModel);

		bool edit ();

		virtual void Visit (Workspace* aWs);
		virtual void Visit (Project* aProj);

    protected:
		MvcModelItemSelection& m_itemModel;
		MvcModelProjectEdit    m_projModel;
		MvcCtrlProjectEdit     m_projCtrl;
		MvcViewCliProject      m_projView;

        bool m_result;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCEDITORCLIITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
