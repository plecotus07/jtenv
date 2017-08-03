// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl) :
    m_ctrl {aCtrl}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::parse (const std::vector<std::string>& aArgs)
{
	if ( (aArgs.empty())
	        || (aArgs[0] == "-h")
	        || (aArgs[0] == "--help") ) {
		DisplayHelp();
		return true;
	} else if ( (aArgs[0] == "-v")
	                || (aArgs[0] == "--version") ) {
		DisplayVersion();
		return true;
	}

	if (!m_ctrl.loadConfig()) {
		std::cerr << "Configuration load error\n";
		return false;
	}
	return true;
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::DisplayHelp () const
{
	std::cout << "\n  jtpm [-v | --version] [-h | --help] [COMMAND]\n\n"
	             "    -v, --version                      - Display version.\n"
	             "    -h, --help                         - Display help.\n";
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::DisplayVersion () const
{
	std::cout << getFullName() << " - v" << getVersion() << '\n';
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
