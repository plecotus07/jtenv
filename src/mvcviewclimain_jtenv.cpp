// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"

#include "projectconf_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "itemfactory_jtenv.hpp"

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

	const Config::UPtr& config { m_configModel.getConfig() };
///\todo assert(config.get() != nullptr);
	if (config.get() == nullptr) return false;

    auto pos {command.find_first_of('=')};
	std::string key {command.substr(0, pos)};
    std::string value {};
    if (key != command) value = command.substr(pos + 1);

    if (key == "user-name") {
		if (value.empty()) std::cout << config->getUserName() << '\n';
		else  if (!m_ctrl.setUserName(value)) {
        	std::cerr << "Edit user name error\n";
            return false;
        }
    } else if (key == "user-email") {
		if (value.empty()) std::cout << config->getUserEmail() << '\n';
		else  if (!m_ctrl.setUserEmail(value)) {
        	std::cerr << "Edit user email error\n";
        	return false;
        }
    } else if (key == "ws-url") {
		if (value.empty()) std::cout << config->getWorkspacesUrl() << '\n';
		else  if (!m_ctrl.setWorkspacesUrl(value)) {
        	std::cerr << "Edit workspaces url error\n";
        	return false;
        }
    }
    else if (key == "path") {
    	std::string addr {};
    	if (aArgs.size() >= 2) {
			addr = aArgs[1];
        }
        ItemFactory fac {config};
        Item::UPtr item {fac.Create(addr)};
        if (!item) {
        	std::cerr << "Invalid address: " << addr << '\n';
			return false;
        }
        std::cout << item->getItemType() << " : " << item->getPath() << '\n';
    } else {
    	std::cerr << "Invalid command: " << command << '\n';
        return false;
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
