// +++ -------------------------------------------------------------------------
#include "mvcapp_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcApp::MvcApp (int aArgc, char* aArgv[]) :
    m_mainView (aArgc, aArgv)
{
}
// -----------------------------------------------------------------------------
bool MvcApp::run ()
{
	m_mainView.update();
	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------