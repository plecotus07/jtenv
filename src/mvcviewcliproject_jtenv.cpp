// +++ -------------------------------------------------------------------------
#include "mvcviewcliproject_jtenv.hpp"

#include "mvcctrlprojectedit_jtenv.hpp"
#include "mvcmodelprojectedit_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliProject::MvcViewCliProject (ArgIterator& aArg, const ArgIterator aArgsEnd, MvcCtrlProjectEdit& aCtrl, MvcModelProjectEdit& aModel) :
    MvcViewCli(aArg, aArgsEnd),
    m_ctrl {aCtrl},
    m_model {aModel},
    m_handlers {{"name", [] (MvcViewCliProject* aView) -> bool {return aView->onFullName();}},
                {"url", [] (MvcViewCliProject* aView) -> bool {return aView->onRemoteRepoUrl();}},
                {"branch", [] (MvcViewCliProject* aView) -> bool {return aView->onDefaultBranch();}},
				{"ccmd", [] (MvcViewCliProject* aView) -> bool {return aView->onCustomCmd();}}}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::submitEdit ()
{
	if (!m_ctrl.submitEdit()) {
        std::cerr << "Edit project error.\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::parse ()
{
    if ( (m_arg == m_argsEnd) ///\todo displayProjInfo
             || (m_arg->substr(0,2) != "--") ) {
        std::cerr << "Missing command.\n";
        return false;
    }
    auto handler = m_handlers.find(m_arg->substr(2));
    if (handler == m_handlers.end()) {
    	std::cerr << "Invalid command: " << *m_arg << '\n';
        return false;
    }

    ++m_arg;

    return (handler->second)(this);
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::containsCommand (const std::string& aCmd)
{
    return (m_handlers.find(aCmd) != m_handlers.end());
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onFullName ()
{
	if (m_arg == m_argsEnd) {
    	std::cerr << "Missing name.\n";
        return false;
    }

    std::string name {*m_arg};

    ++m_arg;
    if (m_arg != m_argsEnd) {
    	std::cerr << "Invalid argument: " << *m_arg << '\n';
        return false;
    }

    m_ctrl.setFullName(name);

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onRemoteRepoUrl ()
{
	if (m_arg == m_argsEnd) {
    	std::cerr << "Missing url.\n";
        return false;
    }

    std::string url {*m_arg};

    ++m_arg;
    if (m_arg != m_argsEnd) {
    	std::cerr << "Invalid argument: " << *m_arg << '\n';
        return false;
    }

    m_ctrl.setRemoteRepoUrl(url);

    return true;

}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onDefaultBranch ()
{
	if (m_arg == m_argsEnd) {
    	std::cerr << "Missing branch name.\n";
        return false;
    }

    std::string branch {*m_arg};

    ++m_arg;
    if (m_arg != m_argsEnd) {
    	std::cerr << "Invalid argument: " << *m_arg << '\n';
        return false;
    }

    m_ctrl.setDefaultBranch(branch);

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onCustomCmd ()
{
	if (m_arg == m_argsEnd) {
		std::cerr << "Missing arguments\n";
		return false;
	}

	std::string arg {*m_arg};

	++m_arg;

	if (arg == "add") return onCustomCmdAdd ();
	else if (arg == "rem") return onCustomCmdRemove ();
	else if (arg == "list") return onCustomCmdList ();


	if (m_arg != m_argsEnd) {
		std::cerr << "Invalid argument: " << *m_arg << '\n';
	   return false;
	}

	if (!m_ctrl.executeCustomCmd(arg)) {
		std::cerr << "Custom command execute error\n";
		return false;
	}

	return true;
}
//// -----------------------------------------------------------------------------
bool MvcViewCliProject::onCustomCmdAdd ()
{
	if (m_arg == m_argsEnd) {
		std::cerr << "1Missing arguments.\n";
		return false;
	}
	std::string name {*m_arg};

	++m_arg;
	if (m_arg == m_argsEnd) {
		std::cerr << "2Missing arguments.\n";
		return false;
	}
	std::string dir {*m_arg};

	++m_arg;
	if (m_arg == m_argsEnd) {
		std::cerr << "3Missing arguments.\n";
		return false;
	}
	std::string cmd {*m_arg};

	++m_arg;
	if (m_arg != m_argsEnd) {
		std::cerr << "Invalid argument: " << *m_arg << '\n';
	   return false;
	}

	if (!m_ctrl.addCustomCmd(name, dir, cmd)) {
		std::cerr << "Add custom command error.\n";
	   return false;
	}

	return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onCustomCmdRemove ()
{
	if (m_arg == m_argsEnd) {
		std::cerr << "Missing arguments.\n";
	   return false;
	}

	std::string name {*m_arg};

	++m_arg;
	if (m_arg != m_argsEnd) {
		std::cerr << "Invalid argument: " << *m_arg << '\n';
	   return false;
	}

	if (!m_ctrl.removeCustomCmd(name)) {
		std::cerr << "Remove custom command error.\n";
	   return false;
	}

	return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onCustomCmdList ()
{
	if (m_arg != m_argsEnd) {
		std::cerr << "Invalid argument: " << *m_arg << '\n';
	   return false;
	}

	for (auto cc : m_model.getCustomCmds()) std::cout << cc.first << "(" << cc.second.first << "): " << cc.second.second << '\n';

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
