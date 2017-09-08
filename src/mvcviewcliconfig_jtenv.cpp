// +++ -------------------------------------------------------------------------
#include "mvcviewcliconfig_jtenv.hpp"

#include "mvcctrlmain_jtenv.hpp"
#include "mvcctrlconfigedit_jtenv.hpp"
#include "mvcmodelconfigedit_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliConfig::MvcViewCliConfig (ArgIterator& aArg, const ArgIterator& aArgsEnd, MvcCtrlConfigEdit& aCtrl, MvcModelConfigEdit& aModel) :
    MvcViewCli(aArg, aArgsEnd),
    m_ctrl {aCtrl},
    m_model {aModel}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::submitEdit ()
{
	return m_ctrl.submitEdit();
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::parse ()
{
    onShow();

    if (m_arg == m_argsEnd) {
    	onDisplayConfig();
        return true;
	} else {
    	std::string key {*m_arg};
		++m_arg;

	    if (key == "user-name") return onUserName();
    	else if (key == "user-email") return onUserEmail();
    }

    std::cerr << "Invalid argument: " << *m_arg << '\n';

    return false;
}
// -----------------------------------------------------------------------------
void MvcViewCliConfig::onShow ()
{
	m_ctrl.prepareEdit();
}
// -----------------------------------------------------------------------------
void MvcViewCliConfig::onDisplayConfig ()
{
	std::cout << "user-name = " << m_model.getUserName() << '\n'
              << "user-email = " << m_model.getUserEmail() << '\n';
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::onUserName ()
{
    if (m_arg == m_argsEnd) {
    	std::cerr << "Missing argument";
    	return false;
    }

	m_ctrl.setUserName(*m_arg);

    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliConfig::onUserEmail ()
{
    if (m_arg == m_argsEnd) {
    	std::cerr << "Missing argument";
    	return false;
    }

    m_ctrl.setUserEmail(*m_arg);

    return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
