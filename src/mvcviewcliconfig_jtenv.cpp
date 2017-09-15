// +++ -------------------------------------------------------------------------
#include "mvcviewcliconfig_jtenv.hpp"

#include "mvcctrlconfigedit_jtenv.hpp"
#include "mvcmodelconfigedit_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliConfig::MvcViewCliConfig (ArgIterator& aArg, const ArgIterator& aArgsEnd, MvcCtrlConfigEdit& aCtrl, MvcModelConfigEdit& aModel) :
    MvcViewCli(aArg, aArgsEnd),
    m_ctrl {aCtrl},
    m_model {aModel},
    m_handlers {{"config", [] (MvcViewCliConfig* aView) -> bool {return aView->onDisplayConfig();}},
	            {"user-name", [] (MvcViewCliConfig* aView) -> bool {return aView->onUserName();}},
	            {"user-email", [] (MvcViewCliConfig* aView) -> bool {return aView->onUserEmail();}}}

{
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::submitEdit ()
{
	if (!m_ctrl.submitEdit()) {
        std::cerr << "Edit config error.\n";
        return false;
    }

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::parse ()
{
    if ( (m_arg == m_argsEnd)
    	 || (m_arg->substr(0, 2) != "--") ) {
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
bool MvcViewCliConfig::containsCommand (const std::string& aCmd)
{
    return (m_handlers.find(aCmd) != m_handlers.end());
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::onDisplayConfig ()
{
	std::cout << "user-name = " << m_model.getUserName() << '\n'
              << "user-email = " << m_model.getUserEmail() << '\n';
    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::onUserName ()
{
    if (m_arg == m_argsEnd) {
    	std::cerr << "Missing argument.\n";
    	return false;
    }

    std::string name {*m_arg};
    ++m_arg;
    if (m_arg != m_argsEnd) {
    	std::cerr << "Invalid argument: " << *m_arg << '\n';
        return false;
    }

	m_ctrl.setUserName(name);

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::onUserEmail ()
{
    if (m_arg == m_argsEnd) {
    	std::cerr << "Missing argument.\n";
    	return false;
    }

    std::string email {*m_arg};
    ++m_arg;
    if (m_arg != m_argsEnd) {
    	std::cerr << "Invalid argument: " << *m_arg << '\n';
        return false;
    }

    m_ctrl.setUserEmail(email);

    return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
