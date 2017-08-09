// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "itemfactory_jtenv.hpp"
#include "visitoritemtype_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliMain::MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel) :
    m_ctrl {aCtrl},
    m_configModel {aConfigModel}
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

    auto pos {command.find_first_of('=')};
	std::string key {command.substr(0, pos)};
    std::string value {};
    if (key != command) value = command.substr(pos + 1);

    if (key == "user-name") return onUserName(value);
    else if (key == "user-email") return onUserEmail(value);
    else if (key == "ws-path") return onWorkspacesDirPath(value);
    else if (key == "path") return onPath(aArgs);
    else if (key == "list") return onListItems(aArgs);
    else {
    	std::cerr << "Invalid command: " << command << '\n';
        return false;
    }

	return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onUserName (const std::string& aValue)
{
	const Config::UPtr& config { m_configModel.getConfig() };
///\todo assert(config.get() != nullptr);
	if (config.get() == nullptr) return false;

    if (aValue.empty()) std::cout << config->getUserName() << '\n';
    else  if (!m_ctrl.setUserName(aValue)) {
        std::cerr << "Edit user name error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onUserEmail (const std::string& aValue)
{
	const Config::UPtr& config { m_configModel.getConfig() };
///\todo assert(config.get() != nullptr);
	if (config.get() == nullptr) return false;

    if (aValue.empty()) std::cout << config->getUserEmail() << '\n';
    else  if (!m_ctrl.setUserEmail(aValue)) {
        std::cerr << "Edit user email error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onWorkspacesDirPath (const std::string& aValue)
{
	const Config::UPtr& config { m_configModel.getConfig() };
///\todo assert(config.get() != nullptr);
	if (config.get() == nullptr) return false;

    if (aValue.empty()) std::cout << config->getWorkspacesDirPath().string() << '\n';
    else  if (!m_ctrl.setWorkspacesDirPath(aValue)) {
        std::cerr << "Edit workspaces path error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onPath (const std::vector<std::string>& aArgs)
{
	const Config::UPtr& config { m_configModel.getConfig() };
///\todo assert(config.get() != nullptr);
	if (config.get() == nullptr) return false;

	std::string addr {};

	if (aArgs.size() >= 2) addr = aArgs[1];

    ItemFactory fac {config};
    Item::UPtr item {fac.Create(addr)};
    if (!item) {
        std::cerr << "Invalid address: " << addr << '\n';
        return false;
    }

    VisitorItemType visitor {};

    item->Accept(&visitor);

    std::cout << visitor.getType() << " : " << item->getPath() << '\n';

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliMain::onListItems (const std::vector<std::string>& aArgs)
{
	const Config::UPtr& config { m_configModel.getConfig() };
///\todo assert(config.get() != nullptr);
	if (config.get() == nullptr) return false;

    std::string root_ws_name {};
    bool cloned_only {false};

    for (int i = 1; i < aArgs.size(); ++i) {
        if (aArgs[i] == "-c") cloned_only = true;
        else if (root_ws_name.empty()) root_ws_name = aArgs[i];
        else {
            std::cerr << "Invalid option: " << aArgs[i] << '\n';
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

    return true;
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::displayHelp () const
{
	std::cout << "\n  jtpm [-v | --version] [-h | --help] [COMMAND]\n\n"
	             "    -v, --version                      - Display version.\n"
	             "    -h, --help                         - Display help.\n";
}
// -----------------------------------------------------------------------------
void MvcViewCliMain::displayVersion () const
{
	std::cout << getFullName() << " - v" << getVersion() << '\n';
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
