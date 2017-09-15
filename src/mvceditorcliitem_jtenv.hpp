// +++ -------------------------------------------------------------------------
#ifndef MVCEDITORCLIITEM_JTENV_HPP
#define MVCEDITORCLIITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"
#include "mvcmodelprojectedit_jtenv.hpp"
#include "mvcctrlprojectedit_jtenv.hpp"
#include "mvcviewcliproject_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelItemSelection;
// +++ -------------------------------------------------------------------------
class MvcEditorCliItem {
	public:
        MvcEditorCliItem (jkpp::MvcViewCli::ArgIterator& aArg, const jkpp::MvcViewCli::ArgIterator& aArgsEnd, MvcModelItemSelection& aItemSelModel);

		bool containsCommand (const std::string& aCmd);
		bool edit ();

    protected:
		MvcModelItemSelection& m_itemSelModel;
		MvcModelProjectEdit    m_projModel;
		MvcCtrlProjectEdit     m_projCtrl;
		MvcViewCliProject      m_projView;
};
// +++ -------------------------------------------------------------------------
class ItemVisitorEdit : public ItemVisitor {
    public:
    	ItemVisitorEdit (MvcViewCliProject& aProjView, MvcCtrlProjectEdit& aProjCtrl);

        operator bool () const { return m_result; };

		virtual void visit (Workspace* aWs);
		virtual void visit (Project* aProj);

    protected:
		MvcCtrlProjectEdit& m_projCtrl;
		MvcViewCliProject&  m_projView;
		bool                m_result;
};
// +++ -------------------------------------------------------------------------
class ItemVisitorContainsCommand : public ItemVisitor {
    public:
    	ItemVisitorContainsCommand (const std::string& aCmd, MvcViewCliProject& aProjView);

        operator bool () const { return m_result; };

		virtual void visit (Workspace* aWs);
		virtual void visit (Project* aProj);

    protected:
		std::string        m_cmd;
		MvcViewCliProject& m_projView;
		bool               m_result;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCEDITORCLIITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
