// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelitem_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, MvcModelItem& aItemModel) :
    m_ctrl {aCtrl},
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel},
    m_itemModel {aItemModel},
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
bool MvcViewCliMain::parse (const std::vector<std::string>& aArgs)
{
	auto arg {aArgs.begin()};

	if ( (aArgs.empty())
	        || (*arg == "-h")
	        || (*arg == "--help") ) {
		displayHelp();
		return true;
	} else if ( (*arg == "-v")
	                || (*arg == "--version") ) {
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

	if ((*arg) == "init") return onInitItem(++arg, aArgs.end());

    auto handler {m_handlers.find(*arg)};
    std::string addr;
    if (handler == m_handlers.end()) {
    	addr = *arg;
        ++arg;
	}

    if (arg == aArgs.end()) {
        std::cerr << "Missing command.\n";
        return false;
    }

    std::string command {};
    command = *arg;
    handler = m_handlers.find(command);
    if (handler == m_handlers.end()) {
        std::cerr << "Invalid command: " << command << '\n';
        return false;
    }
    ++arg;

    auto names {m_addressParser(addr)};
    m_ctrl.selectItem(m_workspacesModel.getItem(names.first, names.second));

    return (handler->second)(this, arg, aArgs.end());
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
	Item::SPtr item {m_itemModel.getItem()};
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
        if ((*aArg)[0] == '-') {
            for (size_t i = 1; i < aArg->size(); ++i) {
                if ((*aArg)[i] == 'c') {
                	if (cloned_only) {
                    	std::cerr << "Duplication of '-c' option.\n";
                        return false;
                    }
	                cloned_only = true;
                } else if ((*aArg)[i] == 'p') {
                	if (with_path) {
                    	std::cerr << "Duplication of '-p' option.\n";
                        return false;
                    }
					with_path = true;
                } else {
		            std::cerr << "Invalid option: -" << (*aArg)[i] << '\n';
                }
            }
        }
        else {
            std::cerr << "Invalid argument: " << *aArg << '\n';
            return false;
        }
    }

	Item::SPtr item {m_itemModel.getItem()};

    if (!item) {
    	for (auto ws : m_workspacesModel) {
        	if (!cloned_only || !ws.second->getPath().empty()) {
            	std::cout << ws.first;
                if (with_path) std::cout << " : " << ws.second->getPath().string();
                std::cout << '\n';
            }
        }
    } else {
    	ProjectsLister lister {cloned_only, with_path};

        item->Accept(lister);

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

	Item::SPtr item { m_itemModel.getItem() };
    if (!item) {
    	std::cout << "Not exists\n";
    	return true;
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

    if (!m_itemModel.getItem()) {
        std::cerr << "Invalid address.\n";
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

    if (!m_itemModel.getItem()) {
        std::cerr << "Invalid address.\n";
        return false;
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
ProjectsLister::ProjectsLister (bool aClonedOnly, bool aWithPath) :
    m_clonedOnly{aClonedOnly},
    m_withPath{aWithPath}
{
}
// -----------------------------------------------------------------------------
void ProjectsLister::Visit (Workspace* aWs)
{
///\todo assert(aWn)

    if (aWs->getPath().empty()) {
        std::cerr << "Workspace " << aWs->getName() << " is not cloned\n";
        return;
    }

    for (auto proj : *aWs) {
        if (!m_clonedOnly || (!proj.second->getRepoPath().empty())) {
            std::cout << proj.first;
            if (m_withPath) std::cout << " : " << proj.second->getPath().string();
            std::cout << '\n';
        }
    }

}
// -----------------------------------------------------------------------------
void ProjectsLister::Visit (Project* aProj)
{
///\todo assert(true)
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
