// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIMAIN_JTENV_HPP
#define MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcviewcli_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcViewCliConfig;
class MvcViewCliCommon;
class MvcViewCliProject;
class MvcModelWorkspaces;
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcViewCli {
	public:
		MvcViewCliMain (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlMain& aCtrl, MvcViewCliConfig& aConfigView, MvcViewCliCommon& aCommonView, MvcViewCliProject& aProjView, MvcModelWorkspaces& aWssModel);

		virtual void update () {};
		virtual bool parse ();
		virtual bool containsCommand (const std::string&) { return false; }

	protected:
		MvcCtrlMain&        m_ctrl;
		MvcViewCliConfig&   m_configView;
    	MvcViewCliCommon&   m_commonView;
		MvcViewCliProject&  m_projView;
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
