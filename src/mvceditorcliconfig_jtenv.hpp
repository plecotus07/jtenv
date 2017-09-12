// +++ -------------------------------------------------------------------------
#ifndef MVCEDITORCLICONFIG_JTENV_HPP
#define MVCEDITORCLICONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "mvcmodelconfigedit_jtenv.hpp"
#include "mvcctrlconfigedit_jtenv.hpp"
#include "mvcviewcliconfig_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfig;
// +++ -------------------------------------------------------------------------
class MvcEditorCliConfig {
	public:
		MvcEditorCliConfig (jkpp::MvcViewCli::ArgIterator& aArg, const jkpp::MvcViewCli::ArgIterator& aArgsEnd, MvcModelConfig& aConfigModel);

		bool containsCommand (const std::string& aCmd) { return m_view.containsCommand(aCmd); }
		bool edit ();

	protected:
		MvcModelConfig&    m_configModel;
		MvcModelConfigEdit m_model;
		MvcCtrlConfigEdit  m_ctrl;
		MvcViewCliConfig   m_view;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCEDITORCLICONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
