// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIPROJECT_JTENV_HPP
#define MVCVIEWCLIPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcviewcli_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlProjectEdit;
class MvcModelProjectEdit;
// +++ -------------------------------------------------------------------------
class MvcViewCliProject : public jkpp::MvcViewCli {
	public:
		MvcViewCliProject (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlProjectEdit& aCtrl, MvcModelProjectEdit& aModel);

		bool submitEdit ();

		virtual void update () {};
		virtual bool parse ();
        virtual bool containsCommand (const std::string& aCmd);

	protected:
		MvcCtrlProjectEdit&  m_ctrl;
		MvcModelProjectEdit& m_model;

		bool onFullName ();
		bool onRemoteRepoUrl ();
		bool onDefaultBranch ();
		bool onCMake ();
		bool onCMakeAdd ();
		bool onCMakeRemove ();
		bool onCMakeList ();

		const Handlers<MvcViewCliProject> m_handlers;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
