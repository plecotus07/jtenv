// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLICOMMON_JTENV_HPP
#define MVCVIEWCLICOMMON_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"

#include <mvcviewcli_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcModelConfig;
class MvcModelWorkspaces;
class MvcModelItemSelection;
// +++ -------------------------------------------------------------------------
class MvcViewCliCommon : public jkpp::MvcViewCli {
	public:
		MvcViewCliCommon (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWssModel, MvcModelItemSelection& aItemSelModel);

		virtual void update () {};
		virtual bool parse ();
        virtual bool containsCommand (const std::string& aCmd);

	protected:
		MvcCtrlMain&           m_ctrl;
        MvcModelConfig&        m_configModel;
		MvcModelWorkspaces&    m_wssModel;
		MvcModelItemSelection& m_itemSelModel;

		bool onPath ();
		bool onListItems ();
		bool onInitItem ();
		bool onStatusItem ();
		bool onCloneItem ();
		bool onClearItem ();
		bool onGit ();

		const Handlers<MvcViewCliCommon> m_handlers;

};
// +++ -------------------------------------------------------------------------
class ItemsLister : public ItemVisitor {
	public:
		ItemsLister (bool aClonedOnly, bool aWithPath);

		virtual void visit (Workspace* aWs);
		virtual void visit (Project* aProj);

	protected:
		bool m_clonedOnly;
		bool m_withPath;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLICOMMON_JTENV_HPP
// +++ -------------------------------------------------------------------------
