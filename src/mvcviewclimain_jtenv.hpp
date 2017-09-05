// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIMAIN_JTENV_HPP
#define MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "addressparser_jtenv.hpp"

#include <mvcviewcli_jkpp.hpp>

#include <vector>
#include <string>
#include <functional>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcModelConfig;
class MvcModelWorkspaces;
class MvcModelWorkspace;
class MvcModelProject;
class MvcModelModel;
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcViewCli {
	public:
		MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, MvcModelWorkspace& aWsModel, MvcModelProject& aProjModel);

		void update () {};
		bool parse (ArgIterator& aArg, const ArgIterator aArgsEnd);

	protected:
		MvcCtrlMain&        m_ctrl;
        MvcModelConfig&     m_configModel;
		MvcModelWorkspaces& m_workspacesModel;
		MvcModelWorkspace&  m_wsModel;
		MvcModelProject&    m_projModel;
        AddressParser       m_addressParser;

		bool onUserName (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onUserEmail (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onPath (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onInitItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onStatusItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCloneItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onClearItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onGit (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMake (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeAdd (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeRemove (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeList (ArgIterator& aArg, const ArgIterator& aArgsEnd);

		void displayHelp () const;
		void displayVersion () const;

		const Handlers<MvcViewCliMain> m_handlers;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
