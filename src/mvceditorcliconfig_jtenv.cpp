// +++ -------------------------------------------------------------------------
#include "mvceditorcliconfig_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcEditorCliConfig::MvcEditorCliConfig (jkpp::MvcViewCli::ArgIterator& aArg, const jkpp::MvcViewCli::ArgIterator& aArgsEnd, MvcModelConfig& aConfigModel) :
    m_configModel {aConfigModel},
    m_model {},
    m_ctrl {m_model, m_configModel},
    m_view {aArg, aArgsEnd, m_ctrl, m_model}
{
}
// -----------------------------------------------------------------------------
bool MvcEditorCliConfig::edit ()
{
    m_ctrl.prepareEdit();

    m_view.show();

	if (!m_view.getResult()) return false; 	// window->showModeal() == mrok
	if (!m_view.submitEdit()) return false;

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
