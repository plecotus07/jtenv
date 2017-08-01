// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"
#include "config_jtenv.hpp"

#include <filesystem_jkpp.hpp>

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (int aArgc, char* aArgv[]) :
	m_args{}
{
	for (int i = 1; i < aArgc; ++i) {
		m_args.push_back(aArgv[i]);
	}
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::update ()
{
	bool displayHelp {m_args.empty()};
	bool displayVersion {false};

	for (auto arg : m_args) {
		if ( (arg == "-h")
		        || (arg == "--help") ) {
        	m_helpView->Update();
			return true;
		}
		else if ( (arg == "-v")
		        || (arg == "--version") ) {
        	m_versionView->Update();
			return true;
		}
	}

	Config config {fs::path(jkpp::getHomeDirPath()) / ".jtenv"};
	config.init();
	if (!config.load()) {
		return false;
	}

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
