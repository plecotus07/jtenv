// +++ -------------------------------------------------------------------------
#include "argsparser_jtenv.hpp"
#include "projectconf_jtenv.hpp"
// +++ -------------------------------------------------------------------------
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ArgsParser::ArgsParser (int aArgc, char* aArgv[]) :
	m_args{}
{
	for (int i = 1; i < aArgc; ++i) {
		m_args.push_back(aArgv[i]);
	}
}
// -----------------------------------------------------------------------------
bool ArgsParser::Parse ()
{
	bool displayHelp {m_args.empty()};
	bool displayVersion {false};

	for (auto arg : m_args) {
		if ( (arg == "-h")
		        || (arg == "--help") ) {
			displayHelp = true;
			break;
		}
		else if ( (arg == "-v")
		        || (arg == "--version") ) {
			displayVersion = true;
			break;
		}
	}

	if (displayHelp) {
		DisplayHelp();
		return true;
	}

	if (displayVersion) {
		DisplayVersion();
		return true;
	}

	return true;
}
// -----------------------------------------------------------------------------
void ArgsParser::DisplayHelp ()
{
	std::cout << "  jtpm [-v | --version] [-h | --help] [ADDR] [COMMAND]\n\n"
	             "    -v, --version                      - Display version.\n"
	             "    -h, --help                         - Display help.\n";
}
// -----------------------------------------------------------------------------
void ArgsParser::DisplayVersion ()
{
	std::cout << jtenv::GetFullName() << " - v" << jtenv::GetVersion() << '\n';
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
