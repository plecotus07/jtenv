// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLICONFIG_JTENV_HPP
#define MVCVIEWCLICONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcviewcli_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlConfigEdit;
class MvcModelConfigEdit;
// +++ -------------------------------------------------------------------------
class MvcViewCliConfig : public jkpp::MvcViewCli {
	public:
		MvcViewCliConfig (ArgIterator& aArg, const ArgIterator& aArgsEnd, MvcCtrlConfigEdit& aCtrl, MvcModelConfigEdit& aConfigEditModel);

		bool submitEdit ();

		virtual void update () {};
		virtual bool parse ();
        virtual bool containsCommand (const std::string& aCmd);

	protected:
		MvcCtrlConfigEdit&  m_ctrl;
		MvcModelConfigEdit& m_model;

		bool onDisplayConfig ();
   		bool onUserName ();
		bool onUserEmail ();

		const Handlers<MvcViewCliConfig> m_handlers;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLICONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
