// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "mvcctrlmain_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl) :
    m_ctrl {aCtrl},
    m_helpView {}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::parse (const std::vector<std::string>& aArgs)
{
	if ( (aArgs.empty())
	        || (aArgs[0] == "-h")
	        || (aArgs[0] == "--help") ) {
		m_helpView.update();
		return true;
	} else if ( (aArgs[0] == "-v")
	                || (aArgs[0] == "--version") ) {
		m_versionView.update();
		return true;
	}

	if (!m_ctrl.loadConfig()) {
		std::cerr << "Configuration load error\n";
		return false;
	}
	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
