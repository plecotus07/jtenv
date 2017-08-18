// +++ -------------------------------------------------------------------------
#include "mvcapp_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcApp::MvcApp () :
    m_configModel {},
    m_workspacesModel {},
    m_gitBuilder {},
    m_mainCtrl {m_configModel, m_workspacesModel, m_gitBuilder},
    m_mainView {m_mainCtrl, m_configModel, m_workspacesModel}
{
}
// -----------------------------------------------------------------------------
bool MvcApp::run (const std::vector<std::string>& aArgs)
{
	return m_mainView.parse(aArgs);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
