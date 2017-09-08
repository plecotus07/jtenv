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
        virtual bool containsCommand (const std::string& aCmd) { return (aCmd == "config"); };

	protected:
		MvcCtrlConfigEdit&  m_ctrl;
		MvcModelConfigEdit& m_model;

		void onShow ();
		void onDisplayConfig ();
   		bool onUserName ();
		bool onUserEmail ();
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLICONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
