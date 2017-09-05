// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelworkspace_jtenv.hpp"
#include "mvcmodelproject_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, MvcModelWorkspace& aWsModel, MvcModelProject& aProjModel) :
    m_ctrl {aCtrl},
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel},
    m_wsModel {aWsModel},
    m_projModel {aProjModel},
    m_addressParser {aWorkspacesModel.getWorkspaces()},
    m_handlers {{"user-name", [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onUserName(aArg, aArgsEnd);}},
                {"user-email", [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onUserEmail(aArg, aArgsEnd);}},
                {"path",  [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onPath(aArg, aArgsEnd);}},
                {"list",  [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onListItems(aArg, aArgsEnd);}},
                {"status",  [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onStatusItem(aArg, aArgsEnd);}},
                {"clone",  [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onCloneItem(aArg, aArgsEnd);}},
                {"clear",  [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onClearItem(aArg, aArgsEnd);}},
                {"git",  [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onGit(aArg, aArgsEnd);}},
                {"cmake",  [] (MvcViewCliMain* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onCMake(aArg, aArgsEnd);}}}
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

	if ((*aArg) == "init") return onInitItem(++aArg, aArgsEnd);

    auto handler {m_handlers.find(*aArg)};
    std::string addr;
    if (handler == m_handlers.end()) {
    	addr = *aArg;
        ++aArg;
	}

    if (aArg == aArgsEnd) {
        std::cerr << "Missing command.\n";
        return false;
    }

    std::string command {};
    command = *aArg;
    handler = m_handlers.find(command);
    if (handler == m_handlers.end()) {
        std::cerr << "Invalid command: " << command << '\n';
        return false;
    }
    ++aArg;

    auto names {m_addressParser(addr)};

    Workspace::SPtr ws {m_workspacesModel.getWorkspace(names.first)};

    if (names.second.empty()) {
	    m_ctrl.selectWorkspace(ws);
    } else if (ws) {
        Project::SPtr proj {ws->getProject(names.second)};
        if (!proj) {
        	std::cerr << "Project '" << names.second << "' not exists in workspace '" << names.first << "'.\n";
            return false;
        }
        m_ctrl.selectProject(proj);
    } else {
        std::cerr << "Workspace '" << names.first << "' not exists.\n";
        return false;
    }


    return (handler->second)(this, aArg, aArgsEnd);
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
bool MvcViewCliMain::onPath (ArgIterator& , const ArgIterator&)
{
	Item::SPtr item {};
    if (auto ws = m_wsModel.getWorkspace(); ws) item = ws;
    else if (auto proj = m_projModel.getProject(); proj) item = proj;

	if (!item) {
        std::cerr << "Invalid address.\n";
        return false;
    }

	std::cout << item->getPath().string() << '\n';

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    bool cloned_only {false};
    bool with_path {false};
    for (; aArg != aArgsEnd; ++aArg) {
        if ( !(*aArg).empty()
             && (*aArg)[0] == '-') {
            for (auto c = aArg->begin() + 1; c != aArg->end(); ++c) {
                if (*c == 'c') {
                	if (cloned_only) {
                    	std::cerr << "Duplication of '-c' option.\n";
                        return false;
                    }
	                cloned_only = true;
                } else if (*c == 'p') {
                	if (with_path) {
                    	std::cerr << "Duplication of '-p' option.\n";
                        return false;
                    }
					with_path = true;
                } else {
		            std::cerr << "Invalid option: -" << *c << '\n';
                }
            }
        }
        else {
            std::cerr << "Invalid argument: " << *aArg << '\n';
            return false;
        }
    }

	Workspace::SPtr sel_ws {m_wsModel.getWorkspace()};

    if (!sel_ws) {
    	for (auto ws : m_workspacesModel) {
        	if (!cloned_only || !ws.second->getPath().empty()) {
            	std::cout << ws.first;
                if (with_path) std::cout << " : " << ws.second->getPath().string();
                std::cout << '\n';
            }
        }
    } else {
        if (sel_ws->getPath().empty()) {
            std::cerr << "Workspace " << sel_ws->getName() << " is not cloned\n";
            return false;
        }

        for (auto proj : *sel_ws) {
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

    if (names.first.empty()) {
    	std::cerr << "Invalid address.\n";
    	return false;
    }

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
bool MvcViewCliMain::onStatusItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    bool show_details {false};
    if ( (aArg != aArgsEnd)
         && ((*aArg) == "-d") ) {
        show_details = true;
    }

	Item::SPtr item {};
    if (auto ws = m_wsModel.getWorkspace(); ws) item = ws;
    else if (auto proj = m_projModel.getProject(); proj) item = proj;

	if (!item) {
        std::cerr << "Invalid address.\n";
        return false;
    }

	std::string details {};
    jkpp::Git::Status status { item->getStatus(details) };

    switch (status) {
   		case jkpp::Git::Status::empty: std::cout << "empty\n"; break;
    	case jkpp::Git::Status::clean: std::cout << "clean\n"; break;
    	case jkpp::Git::Status::not_cloned: std::cout << "not cloned\n"; break;
    	case jkpp::Git::Status::not_commited: std::cout << "not commited\n"; break;
    	case jkpp::Git::Status::not_pushed: std::cout << "not pushed\n"; break;
		case jkpp::Git::Status::unknown:
        default: std::cerr << "Get status error\n";
    }

	if (show_details && !details.empty()) std::cout << details << '\n';

	return false;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onCloneItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg != aArgsEnd) {
    	std::cerr << "Invalid argument: " << *aArg << '\n';
        return false;
    }

    if (!m_ctrl.cloneItem(fs::current_path())) {
    	std::cerr << "Clone item error.\n";
        return false;
    }

   	std::cout << "Item cloned successfully\n";

	return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onClearItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	bool force {false};
    if (aArg != aArgsEnd) {
		if (*aArg != "-f") {
        	std::cerr << "Invalid argument: " << *aArg << '\n';
        	return false;
        }
        force = true;

        ++aArg;
	    if (aArg != aArgsEnd) {
        	std::cerr << "Invalid argument: " << *aArg << '\n';
        	return false;
    	}
    }

    std::string details {};

    if (!m_ctrl.clearItem(force, details)) {
    	if (details.empty()) std::cerr << "Clear item error.\n";
        else std::cout << details;
    } else {
      	std::cout << "Item clear successfully\n";
    }

	return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onGit (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	if (aArg == aArgsEnd) {
    	std::cerr << "Missing git command\n";
        return false;
    }

	std::string git_cmd {};

    for (;aArg != aArgsEnd; ++aArg) git_cmd += *aArg + " ";

    if (!m_ctrl.git(git_cmd)) {
    	std::cerr << "Execute git command error" << '\n';
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onCMake (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) {
    	std::cerr << "Missing arguments\n";
        return false;
    }

    if (*aArg == "add") return onCMakeAdd (aArg, aArgsEnd);
    else if (*aArg == "rem") return onCMakeRemove (aArg, aArgsEnd);
    else if (*aArg == "list") return onCMakeList (aArg, aArgsEnd);

    std::string addr {*aArg};

    ++aArg;
    if (aArg == aArgsEnd) {
    	std::cerr << "Missing arguments.\n";
        return false;
    }
    std::string name {*aArg};

    ++aArg;
    if (aArg != aArgsEnd) {
    	std::cerr << "Invalid argument: " << *aArg << '\n';
        return false;
    }


    if (!m_ctrl.cmakeExecute(*aArg)) {
    	std::cerr << "CMake command execute error\n";
        return false;
    }

    return true;

}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onCMakeAdd (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    ++aArg;
    if (aArg == aArgsEnd) {
    	std::cerr << "Missing arguments.\n";
        return false;
    }
    std::string name {*aArg};

    ++aArg;
    if (aArg == aArgsEnd) {
    	std::cerr << "Missing arguments.\n";
        return false;
    }
    std::string cmd {*aArg};

    ++aArg;
    if (aArg != aArgsEnd) {
    	std::cerr << "Invalid argument: " << *aArg << '\n';
        return false;
    }


    if (!m_ctrl.cmakeAdd(name, cmd)) {
    	std::cerr << "Add CMake command error.\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onCMakeRemove (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    ++aArg;
    if (aArg == aArgsEnd) {
    	std::cerr << "Missing arguments.\n";
        return false;
    }
    std::string name {*aArg};

    ++aArg;
    if (aArg != aArgsEnd) {
    	std::cerr << "Invalid argument: " << *aArg << '\n';
        return false;
    }

    if (!m_ctrl.cmakeRemove(name)) {
    	std::cerr << "Remove CMake command error.\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onCMakeList (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    ++aArg;
    if (aArg != aArgsEnd) {
    	std::cerr << "Invalid argument: " << *aArg << '\n';
        return false;
    }

//    for (auto cmd : m_cmakeModel.getCommands()) std::cout << cmd.first << " = " << cmd.second << '\n';

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
