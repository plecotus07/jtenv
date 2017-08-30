// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel) :
    m_ctrl {aCtrl},
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel},
    m_addressParser {aWorkspacesModel.getWorkspaces()}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::parse (const std::vector<std::string>& aArgs)
{
	std::string command {};
    if (!aArgs.empty()) {
    	command = aArgs[0];
    }

	if ( (command.empty())
	        || (command == "-h")
	        || (command == "--help") ) {
		displayHelp();
		return true;
	} else if ( (command == "-v")
	                || (command == "--version") ) {
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


    bool result {true};
    ArgIterator arg {aArgs.begin() + 1};

    if (command == "user-name") result = onUserName(arg, aArgs.end());
    else if (command == "user-email") result = onUserEmail(arg, aArgs.end());
    else if (command == "path") result = onPath(arg, aArgs.end());
    else if (command == "list") result = onListItems(arg, aArgs.end());
    else if (command == "init") result = onInitItem(arg, aArgs.end());
    else if (command == "status") result = onStatus(arg, aArgs.end());
    else if (command == "clone") result = onClone(arg, aArgs.end());
    else if (command == "clear") result = onItemClear(arg, aArgs.end());
    else if (command == "git") result = onGit(arg, aArgs.end());
    else {
   	std::cerr << "Invalid command: " << command << '\n';
       return false;
    }

	return result;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onUserName (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) std::cout << m_configModel.getUserName() << '\n';
    else  if (!m_ctrl.setUserName(*aArg)) {
        std::cerr << "Edit user name error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onUserEmail (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) std::cout << m_configModel.getUserEmail() << '\n';
    else  if (!m_ctrl.setUserEmail(*aArg)) {
        std::cerr << "Edit user email error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onPath (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	std::string addr {};

    if (aArg != aArgsEnd) addr = *aArg;

	auto names {m_addressParser(addr)};

	Item::SPtr item {m_workspacesModel.getItem(names.first, names.second)};

	if (!item) {
        std::cerr << "Invalid address or workspace is not cloned.\n";
        return false;
    }

	std::cout << item->getPath().string() << '\n';

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    std::string root_ws_name {};
    bool cloned_only {false};
    bool with_path {false};
    for (; aArg != aArgsEnd; ++aArg) {
        if ((*aArg)[0] == '-') {
            for (size_t i = 1; i < aArg->size(); ++i) {
                if ((*aArg)[i] == 'c') cloned_only = true;
                else if ((*aArg)[i] == 'p') with_path = true;
            }
        } else if (root_ws_name.empty()) root_ws_name = *aArg;
        else {
            std::cerr << "Invalid option: " << *aArg << '\n';
            return false;
        }
    }

    if (root_ws_name.empty()) {
    	for (auto ws : m_workspacesModel) {
        	if (!cloned_only || !ws.second->getPath().empty()) {
            	std::cout << ws.first;
                if (with_path) std::cout << " : " << ws.second->getPath().string();
                std::cout << '\n';
            }
        }
    } else {
    	Workspace::SPtr ws {m_workspacesModel.getWorkspace(root_ws_name)};
        if (!ws) {
            std::cerr << "Workspace " << root_ws_name << " not exists\n";
            return false;
        }
        if (ws->getPath().empty()) {
            std::cerr << "Workspace " << root_ws_name << " is not cloned\n";
            return false;
        }

        for (auto proj : *ws) {

        	if (!cloned_only || (!proj.second->getRepoPath().empty())) {
            	std::cout << proj.first;
                if (with_path) std::cout << " : " << proj.second->getPath().string();
                std::cout << '\n';
            }
        }
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onInitItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) {
        std::cerr << "Missing arguments.\n";
        return false;
    }

    auto names { m_addressParser(*aArg)};

    if (names.first.empty()) return false;

    ++aArg;
    if (names.second.empty()) {
    	if (aArg != aArgsEnd) {
        	std::cerr << "Unknown argument: " << *aArg << '\n';
            return false;
        }

    	if (!m_ctrl.initWorkspace(names.first, fs::current_path())) {
        	std::cerr << "Workspace initialization error.\n";
            return false;
        }

        std::cout << "Workspace initialized successfully.\n";
    } else {
        if (aArg == aArgsEnd) {
            std::cerr << "Missing project full name.\n";
            return false;
        }
    	std::string full_name {*aArg};

        ++aArg;
        if (aArg == aArgsEnd) {
            std::cerr << "Missing project repository URL.\n";
            return false;
        }

        std::string repo_url {*aArg};

        bool clone {false};
        ++aArg;
        if (aArg != aArgsEnd) {
        	if ((*aArg) == "-c") {
				clone = true;
            } else {
            	std::cerr << "Invalid argument: " << *aArg << '\n';
                return false;
            }
		}

		if (!m_ctrl.initProject(names.first, names.second, full_name, repo_url, clone)) {
        	std::cerr << "Project initialization error.\n";
            return false;
        }
        std::cout << "Project initialized successfully.\n";
    }

	return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onStatus (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	std::string addr;
    bool showDetails {false};

    for (;aArg != aArgsEnd; ++aArg) {
    	if (*aArg == "-d"){
        	if (showDetails) {
            	std::cerr << "Invalid argument: -d\n";
                return false;
            }
            showDetails = true;
        } else {
        	if (!addr.empty()) {
        		std::cerr << "Invalid argument: " + *aArg + '\n';
	            return false;
    	    }
			addr = *aArg;
		}
    }

    auto names {m_addressParser(addr)};
    if (names.first.empty()) {
    	std::cerr << "Invalid address: " << addr << '\n';
    	return false;
    }

	Item::SPtr item { m_workspacesModel.getItem(names.first, names.second) };
    if (!item) {
    	std::cout << "Not exists\n";
    	return true;
    }

	std::string statusDetails {};
    jkpp::Git::Status status { item->getStatus(statusDetails) };

    switch (status) {
   		case jkpp::Git::Status::empty: std::cout << "Empty\n"; break;
    	case jkpp::Git::Status::clean: std::cout << "Clean\n"; break;
    	case jkpp::Git::Status::not_cloned: std::cout << "Not cloned\n"; break;
    	case jkpp::Git::Status::not_commited: std::cout << "Not commited\n"; break;
    	case jkpp::Git::Status::not_pushed: std::cout << "Not pushed\n"; break;
		case jkpp::Git::Status::unknown:
        default: std::cerr << "Get status error\n";
    }

	if (showDetails && !statusDetails.empty()) std::cout << statusDetails << '\n';

	return false;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onClone (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	std::string addr;
    if (aArg == aArgsEnd) {
    	std::cerr << "Missing item address.\n";
        return false;
    }

    addr = *aArg;

    ++aArg;
    if (aArg != aArgsEnd) {
    	std::cerr << "Invalid argument: " << *aArg << '\n';
        return false;
    }

	auto names {m_addressParser(addr)};
    if (names.first.empty()) {
    	std::cerr << "Invalid address: " << addr << '\n';
        return false;
    }

    if (names.second.empty()) {
    	if (!m_ctrl.cloneWorkspace(names.first, fs::current_path())) {
	    	std::cerr << "Clone workspace error\n";
    	    return false;
        } else {
        	std::cout << "Workspace cloned successfully\n";
        }
	} else {
    	if (!m_ctrl.cloneProject(names.first, names.second)) {
	    	std::cerr << "Clone project error\n";
    	    return false;
        } else {
        	std::cout << "Project cloned successfully\n";
        }
	}

	return false;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onItemClear (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	std::string addr {};
    bool        force {false};

    for (;aArg != aArgsEnd; ++aArg) {
    	if (*aArg == "-f"){
        	if (force) {
            	std::cerr << "Invalid argument: -f\n";
                return false;
            }
            force = true;
        } else {
        	if (!addr.empty()) {
        		std::cerr << "Invalid argument: " + *aArg + '\n';
	            return false;
    	    }
			addr = *aArg;
		}
    }

	auto names {m_addressParser(addr)};
    if (names.first.empty()) {
    	std::cerr << "Invalid address: " << addr << '\n';
        return false;
    }

    std::string details {};

    if (names.second.empty()) {
    	if (!m_ctrl.clearWorkspace(names.first, details, force)) {
        	if (details.empty()) std::cerr << "Clear workspace error\n";
            else std::cout << details;

            return false;
        } else {
        	std::cout << "Workspace clear successfully\n";
        }
	} else {
    	if (!m_ctrl.clearProject(names.first, names.second, details, force)) {
        	if (details.empty()) std::cerr << "Clear project error\n";
            else std::cout << details;

  		    return false;
        } else {
        	std::cout << "Project clear successfully\n";
        }
	}

	return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onGit (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	if (aArg == aArgsEnd) {
    	std::cerr << "Missing arguments\n";
        return false;
    }

	std::string addr {};
	if (*aArg != "--") {
        addr = *aArg;
        ++aArg;
    }

    auto names {m_addressParser(addr)};
    if (names.first.empty()) {
    	std::cerr << "Invalid address: " << addr << '\n';
        return false;
    }

    if ( (aArg == aArgsEnd)
         || (*aArg != "--") ) {
    	std::cerr << "Missing arguments";
        return false;
    }

    ++aArg;
	if (aArg == aArgsEnd) {
    	std::cerr << "Missing git command\n";
        return false;
    }

	std::string git_cmd {};

    for (;aArg != aArgsEnd; ++aArg) git_cmd += *aArg + " ";

    if (!m_ctrl.git(names.first, names.second, git_cmd)) {
    	std::cerr << "Execute git command error" << '\n';
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::displayHelp () const
{
	std::cout << "\n  jtpm [-v | --version] [-h | --help] [COMMAND]\n\n"
	             "    -v, --version                      - Display version.\n"
	             "    -h, --help                         - Display help.\n"
                 "\n    user-name [USER_NAME]              - Set or get user name.\n"
                 "    user-email [USER_EMAIL]            - Set or get user email.\n"
                 "\n    path [ADDR]                        - Get item path.\n"
                 "\n    list [-c]                          - List workspaces.\n"
                 "      -c - only cloned\n"
                 "      -p - with path\n"
                 "    list WS_NAME [-c]                  - List workspace projects.\n"
                 "      -c - only cloned\n"
                 "      -p - with path\n"
                 "\n    init WS_NAME                       - Init workspace.\n"
	             "    init ADDR FULL_NAME REPO_URL [-c]  - Init project.\n"
                 "      -c - clone\n"
                 "\n    status [ADDR] [-d]                 - get item status\n"
                 "      -d - display details\n"
                 "\n    clone [ADDR]                       - clone item\n"
                 "\n    clear [ADDR] [-f]                  - clear item\n"
                 "      -f - force\n"
                 "\n    git [ADDR] -- [COMMAND]            - execute Git command\n"
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
