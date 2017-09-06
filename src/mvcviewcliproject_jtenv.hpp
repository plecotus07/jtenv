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
		MvcViewCliProject (MvcCtrlMain& aCtrl, MvcModelProject& aProjModel);

		virtual void update () {};
		virtual bool parse (ArgIterator& aArg, const ArgIterator aArgsEnd);
        virtual bool containsCommand (const std::string& aCmd);

	protected:
		MvcCtrlMain&        m_ctrl;
		MvcModelProject&    m_projModel;

		bool onCMake (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeAdd (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeRemove (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeList (ArgIterator& aArg, const ArgIterator& aArgsEnd);

		const Handlers<MvcViewCliProject> m_handlers;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
