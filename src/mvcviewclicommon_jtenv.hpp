// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLICOMMON_JTENV_HPP
#define MVCVIEWCLICOMMON_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcviewcli_jkpp.hpp>

#include <vector>
#include <string>
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
class MvcViewCliCommon : public jkpp::MvcViewCli {
	public:
		MvcViewCliCommon (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWssModel, MvcModelWorkspace& aWsModel, MvcModelProject& aProjModel);

		virtual void update () {};
		virtual bool parse (ArgIterator& aArg, const ArgIterator aArgsEnd);
        virtual bool containsCommand (const std::string& aCmd);

	protected:
		MvcCtrlMain&        m_ctrl;
        MvcModelConfig&     m_configModel;
		MvcModelWorkspaces& m_wssModel;
		MvcModelWorkspace&  m_wsModel;
		MvcModelProject&    m_projModel;

		bool onUserName (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onUserEmail (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onPath (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onInitItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onStatusItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCloneItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onClearItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onGit (ArgIterator& aArg, const ArgIterator& aArgsEnd);

		const Handlers<MvcViewCliCommon> m_handlers;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLICOMMON_JTENV_HPP
// +++ -------------------------------------------------------------------------
