// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIMAIN_JTENV_HPP
#define MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcviewcli_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcEditorCliConfig;
class MvcViewCliCommon;
class MvcEditorCliItem;
class MvcModelWorkspaces;
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcViewCli {
	public:
		MvcViewCliMain (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlMain& aCtrl, MvcEditorCliConfig& aConfigEditor, MvcViewCliCommon& aCommonView, MvcEditorCliItem& aItemEditor, MvcModelWorkspaces& aWssModel);

		virtual void update () {};
		virtual bool parse ();
		virtual bool containsCommand (const std::string&) { return false; }

	protected:
		MvcCtrlMain&        m_ctrl;
		MvcEditorCliConfig& m_configEditor;
    	MvcViewCliCommon&   m_commonView;
		MvcEditorCliItem&   m_itemEditor;
		MvcModelWorkspaces& m_wssModel;

		void onDisplayHelp () const;
		void onDisplayVersion () const;

		bool onConfig ();
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
