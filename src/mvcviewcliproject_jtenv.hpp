// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIPROJECT_JTENV_HPP
#define MVCVIEWCLIPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcviewcli_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcModelProject;
// +++ -------------------------------------------------------------------------
class MvcViewCliProject : public jkpp::MvcViewCli {
	public:
		MvcViewCliProject (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlMain& aCtrl, MvcModelProject& aProjModel);

		virtual void update () {};
		virtual bool parse ();
        virtual bool containsCommand (const std::string& aCmd);

	protected:
		MvcCtrlMain&        m_ctrl;
		MvcModelProject&    m_projModel;

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
