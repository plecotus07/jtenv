// +++ -------------------------------------------------------------------------
#include "mvcviewclicommon_jtenv.hpp"

#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelitemselection_jtenv.hpp"
#include "addressparser_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliCommon::MvcViewCliCommon (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWssModel, MvcModelItemSelection& aItemSelModel) :
    MvcViewCli(aArg, aArgsEnd),
    m_ctrl {aCtrl},
    m_configModel {aConfigModel},
    m_wssModel {aWssModel},
    m_itemSelModel {aItemSelModel},
    m_handlers {{"path",  [] (MvcViewCliCommon* aView) -> bool {return aView->onPath();}},
                {"list",  [] (MvcViewCliCommon* aView) -> bool {return aView->onListItems();}},
                {"init",  [] (MvcViewCliCommon* aView) -> bool {return aView->onInitItem();}},
                {"status",  [] (MvcViewCliCommon* aView) -> bool {return aView->onStatusItem();}},
                {"clone",  [] (MvcViewCliCommon* aView) -> bool {return aView->onCloneItem();}},
                {"clear",  [] (MvcViewCliCommon* aView) -> bool {return aView->onClearItem();}},
                {"git",  [] (MvcViewCliCommon* aView) -> bool {return aView->onGit();}}}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::parse ()
{
    if ( (m_arg == m_argsEnd)
             || (m_arg->substr(0,2) != "--") ) {
        std::cerr << "Missing command.\n";
        return false;
    }

    auto handler = m_handlers.find(m_arg->substr(2));
///\todo assert (handler != m_handlers.end();

    ++m_arg;

    return (handler->second)(this);
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::containsCommand (const std::string& aCmd)
{
    return (m_handlers.find(aCmd) != m_handlers.end());
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::onPath ()
{
	Item::SPtr item {m_itemSelModel.getItem()};

	if (!item) {
        std::cerr << "Invalid address.\n";
        return false;
    }

	std::cout << item->getPath().string() << '\n';

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::onListItems ()
{
    bool cloned_only {false};
    bool with_path {false};
    for (; m_arg != m_argsEnd; ++m_arg) {
        if ( !(*m_arg).empty()
             && (*m_arg)[0] == '-') {
            for (auto c = m_arg->begin() + 1; c != m_arg->end(); ++c) {
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
            std::cerr << "Invalid argument: " << *m_arg << '\n';
            return false;
        }
    }

	Item::SPtr item {m_itemSelModel.getItem()};
	if (item) {
		auto lister {ItemsLister(cloned_only, with_path)};
		item->accept(lister);
	} else {
    	for (auto ws : m_wssModel) {
        	if (!cloned_only || !ws.second->getPath().empty()) {
            	std::cout << ws.first;
                if (with_path) std::cout << " : " << ws.second->getPath().string();
                std::cout << '\n';
            }
        }
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::onInitItem ()
{
    if (m_arg == m_argsEnd) {
        std::cerr << "Missing arguments.\n";
        return false;
    }

    auto names {AddressParser{m_wssModel.getWorkspaces()}(*m_arg)};

    if (names.first.empty()) {
    	std::cerr << "Invalid address.\n";
    	return false;
    }

    ++m_arg;
    if (names.second.empty()) {
    	if (m_arg != m_argsEnd) {
        	std::cerr << "Unknown argument: " << *m_arg << '\n';
            return false;
        }

    	if (!m_ctrl.initWorkspace(names.first, fs::current_path())) {
        	std::cerr << "Workspace initialization error.\n";
            return false;
        }

        std::cout << "Workspace initialized successfully.\n";
    } else {
        if (m_arg == m_argsEnd) {
            std::cerr << "Missing project full name.\n";
            return false;
        }
    	std::string full_name {*m_arg};

        ++m_arg;
        if (m_arg == m_argsEnd) {
            std::cerr << "Missing project repository URL.\n";
            return false;
        }

        std::string repo_url {*m_arg};

        bool clone {false};
        ++m_arg;
        if (m_arg != m_argsEnd) {
        	if ((*m_arg) == "-c") {
				clone = true;
            } else {
            	std::cerr << "Invalid argument: " << *m_arg << '\n';
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
bool MvcViewCliCommon::onStatusItem ()
{
    bool show_details {false};
    if ( (m_arg != m_argsEnd)
         && ((*m_arg) == "-d") ) {
        show_details = true;
    }

	Item::SPtr item {m_itemSelModel.getItem()};
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
bool MvcViewCliCommon::onCloneItem ()
{
    if (m_arg != m_argsEnd) {
    	std::cerr << "Invalid argument: " << *m_arg << '\n';
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
bool MvcViewCliCommon::onClearItem ()
{
	bool force {false};
    if (m_arg != m_argsEnd) {
		if (*m_arg != "-f") {
        	std::cerr << "Invalid argument: " << *m_arg << '\n';
        	return false;
        }
        force = true;

        ++m_arg;
	    if (m_arg != m_argsEnd) {
        	std::cerr << "Invalid argument: " << *m_arg << '\n';
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
bool MvcViewCliCommon::onGit ()
{
	if (m_arg == m_argsEnd) {
    	std::cerr << "Missing git command\n";
        return false;
    }

	std::string git_cmd {};

    for (;m_arg != m_argsEnd; ++m_arg) git_cmd += *m_arg + " ";

    if (!m_ctrl.git(git_cmd)) {
    	std::cerr << "Execute git command error" << '\n';
        return false;
    }

    return true;
}
// +++ -------------------------------------------------------------------------
ItemsLister::ItemsLister (bool aClonedOnly, bool aWithPath) :
	m_clonedOnly {aClonedOnly},
	m_withPath {aWithPath}
{
}
// -----------------------------------------------------------------------------
void ItemsLister::Visit (Workspace* aWs)
{
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
void ItemsLister::Visit (Project*)
{

}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
