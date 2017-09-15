// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvceditorcliconfig_jtenv.hpp"
#include "mvcviewclicommon_jtenv.hpp"
#include "mvceditorcliitem_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "addressparser_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlMain& aCtrl,
                                MvcEditorCliConfig& aConfigEditor, MvcViewCliCommon& aCommonView,
								MvcEditorCliItem& aItemEditor, MvcModelWorkspaces& aWssModel) :
    MvcViewCli(aArg, aArgsEnd),
    m_ctrl {aCtrl},
    m_configEditor {aConfigEditor},
    m_commonView {aCommonView},
    m_itemEditor {aItemEditor},
    m_wssModel {aWssModel}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::parse ()
{
	if ( (m_arg == m_argsEnd)
	        || (*m_arg == "-h")
	        || (*m_arg == "--help") ) {
		onDisplayHelp();
		return true;
	} else if ( (*m_arg == "-v")
	                || (*m_arg == "--version") ) {
		onDisplayVersion();
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
    if (m_arg->substr(0,2) != "--") {
    	addr = *m_arg;
        ++m_arg;
    }

    if ( (m_arg == m_argsEnd)
         || (m_arg->substr(0,2) != "--") ){
        std::cerr << "Missing command.\n";
        return false;
    }

    std::string cmd {m_arg->substr(2)};

    if (m_configEditor.containsCommand(cmd)) return m_configEditor.edit();

    auto names {AddressParser{m_wssModel.getWorkspaces()}(addr)};
    m_ctrl.selectItem(m_wssModel.getItem(names.first, names.second));

	if (m_commonView.containsCommand(cmd)) return m_commonView.parse();
    if (m_itemEditor.containsCommand(cmd)) return m_itemEditor.edit();

    std::cerr << "Invalid command: '" << cmd << "'";
    if (!addr.empty()) std::cerr << " for item: " << addr;
    std::cerr << '\n';

    return false;
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::onDisplayHelp () const
{
	std::cout << "\n  jtpm [-v | --version] [-h | --help] [ADDR] [COMMAND]\n\n"
	               "    -v, --version                      - Display version.\n"
	               "    -h, --help                         - Display help.\n"

                 "\n    --config                           - Display configuration\n"
                   "    --user-name USER_NAME              - Set or get user name.\n"
                   "    --user-email USER_EMAIL            - Set or get user email.\n"

                 "\n    [ADDR] --path                      - Get item path.\n"

                 "\n    --list [-cp]                       - List workspaces.\n"
                   "    WS_NAME --list [-cp]               - List workspace projects.\n"
                   "      -c - only cloned\n"
                   "      -p - with path\n"

                 "\n    --init WS_NAME                     - Init workspace.\n"
	               "    --init ADDR REPO_URL [-c]          - Init project.\n"
                   "      -c - clone\n"

                 "\n    [ADDR] --status [-d]               - get item status\n"
                   "      -d - display details\n"

                 "\n    [ADDR] --clone                     - clone item\n"

                 "\n    [ADDR] --clear [-f]                - clear item\n"
                   "      -f - force\n"

                 "\n    [ADDR] --git [COMMAND]             - execute Git command\n"

                 "\n  If ADDR item is project:\n"
                   "    [ADDR] --ccmd [add] [rem] [list]   - Custom commands manager\n"
                   "      NAME                 - execute NAME command in ADDR pr\n"
                   "      add NAME DIR COMMAND - add command\n"
                   "      rem NAME             - remove command\n"
                   "      list                 - list commands\n"
			  	 "\n";
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::onDisplayVersion () const
{
	std::cout << getFullName() << " - v" << getVersion() << '\n';
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
