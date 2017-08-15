// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel) :
    m_ctrl {aCtrl},
    m_configModel {aConfigModel},
    m_workspacesModel {aWorkspacesModel}
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

    bool result {true};
    ArgIterator arg {aArgs.begin() + 1};

    if (command == "user-name") result = onUserName(arg, aArgs.end());
    else if (command == "user-email") result = onUserEmail(arg, aArgs.end());
    else if (command == "ws-path") result = onWorkspacesDirPath(arg, aArgs.end());
    else if (command == "path") result = onPath(arg, aArgs.end());
    else if (command == "list") result = onListItems(arg, aArgs.end());
    else if (command == "init") result = onInitItem(arg, aArgs.end());
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
bool MvcViewCliMain::onWorkspacesDirPath (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) std::cout << m_configModel.getWorkspacesDirPath().string() << '\n';
    else  if (!m_ctrl.setWorkspacesDirPath(*aArg)) {
        std::cerr << "Edit workspaces path error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onPath (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
	std::string addr {};

    if (aArg != aArgsEnd) addr = *aArg;

    

    return false;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
/*
    std::string root_ws_name {};
    bool cloned_only {false};

    for (; aArg != aArgsEnd; ++aArg) {
        if (*aArg == "-c") cloned_only = true;
        else if (root_ws_name.empty()) root_ws_name = *aArg;
        else {
            std::cerr << "Invalid option: " << *aArg << '\n';
            return false;
        }
    }

    if (root_ws_name.empty()) {

	   	std::vector<fs::path> items {};
    	std::copy(fs::directory_iterator(config->getWorkspacesDirPath()), fs::directory_iterator(), std::back_inserter(items));
        for (auto item_path : items) {
			std::string ws_name {};
            if (item_path.extension() == ".git") ws_name = item_path.stem().string();

            if (ws_name.empty()) continue;

            fs::path ws_path {config->getWsPath(ws_name)};

			if (!ws_path.empty() || !cloned_only) std::cout << ws_name << '\n';
        }

    } else {
        if (!fs::exists(config->getWorkspacesDirPath() / (root_ws_name + ".git"))) {
        	std::cerr << "Workspace '" << root_ws_name << "' not exists.\n";
            return false;
        }

        fs::path ws_path {config->getWsPath(root_ws_name)};

        if (ws_path.empty()) {
        	std::cerr << "Workspace '" << root_ws_name << "' is not cloned.\n";
        	return false;
        }

	   	std::vector<fs::path> items {};
    	std::copy(fs::directory_iterator(ws_path), fs::directory_iterator(), std::back_inserter(items));

        for (auto item_path : items) {
            if (!fs::exists(item_path / "project.conf")) continue;

            std::string proj_name {item_path.filename().string()};

			if (fs::exists(item_path / (proj_name + "_repo")) || !cloned_only) std::cout << proj_name << '\n';
        }
    }
*/
    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onInitItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
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
                 "    ws-dir [WS_DIR_PATH]               - Set or get workspaces directory path.\n"
                 "\n    path [ADDR]                        - Get item path.\n"
                 "\n    list [-c]                          - List workspaces.\n"
                 "      -c - only cloned\n"
                 "    list WS_NAME [-c]                  - List workspace projects.\n"
                 "      -c - only cloned\n"
                 "\n    init WS_NAME                       - Init workspace.\n"
	             "    init ADDR FULL_NAME REPO_URL [-c]    - Init project.\n"
                 "      -c - clone\n";
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::displayVersion () const
{
	std::cout << getFullName() << " - v" << getVersion() << '\n';
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
