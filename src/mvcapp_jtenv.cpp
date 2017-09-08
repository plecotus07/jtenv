// +++ -------------------------------------------------------------------------
#include "mvcapp_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcApp::MvcApp (const std::vector<std::string>& aArgs) :
    jkpp::MvcApp(aArgs),
    m_configModel {},
    m_configEditModel {},
    m_workspacesModel {},
    m_wsModel {},
    m_projModel {},
    m_gitBuilder {},
    m_mainCtrl {m_configModel, m_workspacesModel, m_wsModel, m_projModel, m_gitBuilder},
    m_configEditCtrl {m_configEditModel, m_configModel},
    m_commonView {m_arg, m_args.end(), m_mainCtrl, m_configModel, m_workspacesModel, m_wsModel, m_projModel},
    m_projView {m_arg, m_args.end(), m_mainCtrl, m_projModel},
    m_configView {m_arg, m_args.end(), m_configEditCtrl, m_configEditModel},
    m_mainView {m_arg, m_args.end(), m_mainCtrl, m_configView, m_commonView, m_projView, m_workspacesModel}
{
}
// -----------------------------------------------------------------------------
bool MvcApp::run ()
{
	m_mainView.show();
	return m_mainView.getResult();
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
