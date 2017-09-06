// +++ -------------------------------------------------------------------------
#include "mvcapp_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcApp::MvcApp () :
    m_configModel {},
    m_workspacesModel {},
    m_wsModel {},
    m_projModel {},
    m_gitBuilder {},
    m_mainCtrl {m_configModel, m_workspacesModel, m_wsModel, m_projModel, m_gitBuilder},
    m_commonView {m_mainCtrl, m_configModel, m_workspacesModel, m_wsModel, m_projModel},
    m_projView {m_mainCtrl, m_projModel},
    m_mainView {m_mainCtrl, m_commonView, m_projView, m_workspacesModel}
{
}
// -----------------------------------------------------------------------------
bool MvcApp::run (const std::vector<std::string>& aArgs)
{
    auto arg = aArgs.begin();
	return m_mainView.parse(arg, aArgs.end());
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
