// +++ -------------------------------------------------------------------------
#include "mvcviewclicommon_jtenv.hpp"

#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelworkspace_jtenv.hpp"
#include "mvcmodelproject_jtenv.hpp"
#include "addressparser_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliCommon::MvcViewCliCommon (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWssModel, MvcModelWorkspace& aWsModel, MvcModelProject& aProjModel) :
    m_ctrl {aCtrl},
    m_configModel {aConfigModel},
    m_wssModel {aWssModel},
    m_wsModel {aWsModel},
    m_projModel {aProjModel},
    m_handlers {{"user-name", [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onUserName(aArg, aArgsEnd);}},
                {"user-email", [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onUserEmail(aArg, aArgsEnd);}},
                {"path",  [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onPath(aArg, aArgsEnd);}},
                {"list",  [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onListItems(aArg, aArgsEnd);}},
                {"init",  [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onInitItem(aArg, aArgsEnd);}},
                {"status",  [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onStatusItem(aArg, aArgsEnd);}},
                {"clone",  [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onCloneItem(aArg, aArgsEnd);}},
                {"clear",  [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onClearItem(aArg, aArgsEnd);}},
                {"git",  [] (MvcViewCliCommon* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onGit(aArg, aArgsEnd);}}}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::parse (ArgIterator& aArg, const ArgIterator aArgsEnd)
{
    if ( (aArg == aArgsEnd)
             || (aArg->substr(0,2) != "--") ) {
        std::cerr << "Missing command.\n";
        return false;
    }

    auto handler = m_handlers.find(aArg->substr(2));
///\todo assert (handler != m_handlers.end();

    ++aArg;

    return (handler->second)(this, aArg, aArgsEnd);
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::containsCommand (const std::string& aCmd)
{
    return (m_handlers.find(aCmd) != m_handlers.end());
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::onUserName (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) std::cout << m_configModel.getUserName() << '\n';
    else  if (!m_ctrl.setUserName(*aArg)) {
        std::cerr << "Edit user name error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::onUserEmail (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) std::cout << m_configModel.getUserEmail() << '\n';
    else  if (!m_ctrl.setUserEmail(*aArg)) {
        std::cerr << "Edit user email error\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliCommon::onPath (ArgIterator& , const ArgIterator&)
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
bool MvcViewCliCommon::onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd)
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
    	for (auto ws : m_wssModel) {
        	if (!cloned_only || !ws.second->getPath().empty()) {
            	std::cout << ws.first;
                if (with_path) std::cout << " : " << ws.second->getPath().string();
                std::cout << '\n';
            }
        }
    } else if (!(m_projModel.getProject())) {
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
bool MvcViewCliCommon::onInitItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) {
        std::cerr << "Missing arguments.\n";
        return false;
    }

    auto names {AddressParser{m_wssModel.getWorkspaces()}(*aArg)};

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
bool MvcViewCliCommon::onStatusItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
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
bool MvcViewCliCommon::onCloneItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
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
bool MvcViewCliCommon::onClearItem (ArgIterator& aArg, const ArgIterator& aArgsEnd)
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
bool MvcViewCliCommon::onGit (ArgIterator& aArg, const ArgIterator& aArgsEnd)
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
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
