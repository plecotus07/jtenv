// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcviewclicommon_jtenv.hpp"
#include "mvcviewcliproject_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "addressparser_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl, MvcViewCliCommon& aCommonView, MvcViewCliProject& aProjView, MvcModelWorkspaces& aWssModel) :
    m_ctrl {aCtrl},
    m_commonView {aCommonView},
    m_projView {aProjView},
    m_wssModel {aWssModel}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::parse (ArgIterator& aArg, const ArgIterator aArgsEnd)
{
	if ( (aArg == aArgsEnd)
	        || (*aArg == "-h")
	        || (*aArg == "--help") ) {
		displayHelp();
		return true;
	} else if ( (*aArg == "-v")
	                || (*aArg == "--version") ) {
		displayVersion();
		return true;
	}

    if (!m_ctrl.loadConfig()) {
		std::cerr << "Configuration load error\n";
		return false;
	}

	// std::cerr << "+++ -------------------\n";
    // for (auto ws : m_workspacesModel) {
    //     std::cout << ws.second->getName() << " : " << ws.second->getPath().string() << '\n';
	// 	for (auto proj : *(ws.second)) {
    //     	std::cout << "  " << proj.second->getName() << " : " << proj.second->getPath().string() << '\n';
	// 	}
    // }
	// std::cerr << "+++ -------------------\n";

    std::string addr {};
    if (aArg->substr(0,2) != "--") {
    	addr = *aArg;
        ++aArg;
    }

    if ( (aArg == aArgsEnd)
         || (aArg->substr(0,2) != "--") ){
        std::cerr << "Missing command.\n";
        return false;
    }

    std::string cmd {aArg->substr(2)};

    auto names {AddressParser{m_wssModel.getWorkspaces()}(addr)};
    Workspace::SPtr ws {m_wssModel.getWorkspace(names.first)};
    Project::SPtr proj {};
    if (ws) proj = ws->getProject(names.second);

    if (!proj) m_ctrl.selectWorkspace(ws);
    else m_ctrl.selectProject(proj);

	if (m_commonView.containsCommand(cmd)) return m_commonView.parse(aArg, aArgsEnd);

    if (proj && m_projView.containsCommand(cmd)) return m_projView.parse(aArg, aArgsEnd);

    std::cerr << "Invalid command: " << cmd << '\n';
    return false;
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::displayHelp () const
{
	std::cout << "\n  jtpm [-v | --version] [-h | --help] [COMMAND]\n\n"
	               "    -v, --version                      - Display version.\n"
	               "    -h, --help                         - Display help.\n"

                 "\n    user-name [USER_NAME]              - Set or get user name.\n"
                   "    user-email [USER_EMAIL]            - Set or get user email.\n"

                 "\n    [ADDR] path                        - Get item path.\n"

                 "\n    list [-c]                          - List workspaces.\n"
                   "      -c - only cloned\n"
                   "      -p - with path\n"
                   "    WS_NAME list [-c]                  - List workspace projects.\n"
                   "      -c - only cloned\n"
                   "      -p - with path\n"

                 "\n    init WS_NAME                       - Init workspace.\n"
	               "    init ADDR FULL_NAME REPO_URL [-c]  - Init project.\n"
                   "      -c - clone\n"

                 "\n    [ADDR] status [-d]                 - get item status\n"
                   "      -d - display details\n"

                 "\n    [ADDR] clone                       - clone item\n"

                 "\n    [ADDR] clear [-f]                  - clear item\n"
                   "      -f - force\n"

                 "\n    [ADDR] git [COMMAND]               - execute Git command\n"

                 "\n    [ADDR] cmake [add] [rem] [list] [NAME] - CMake commands manager\n"
                   "      NAME             - execute NAME command in ADDR project\n"
                   "      add NAME COMMAND - add command\n"
                   "      rem NAME         - remove command\n"
                   "      list             - list commands\n"
			  	 "\n";
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::displayVersion () const
{
	std::cout << getFullName() << " - v" << getVersion() << '\n';
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
