// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIMAIN_JTENV_HPP
#define MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcviewcli_jkpp.hpp>

#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcViewCliCommon;
class MvcModelWorkspaces;
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcViewCli {
	public:
		MvcViewCliMain (MvcCtrlMain& aCtrl, MvcViewCliCommon& aCommonView, MvcModelWorkspaces& aWssModel);

		virtual void update () {};
		virtual bool parse (ArgIterator& aArg, const ArgIterator aArgsEnd);
		virtual bool containsCommand (const std::string&) { return false; }

	protected:
		MvcCtrlMain&        m_ctrl;
    	MvcViewCliCommon&   m_commonView;
		MvcModelWorkspaces& m_wssModel;

		void displayHelp () const;
		void displayVersion () const;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
