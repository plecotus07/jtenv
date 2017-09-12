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
    m_handlers {{"name", [] (MvcViewCliProject* aView) -> bool {return aView->onFullName();}}}
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

    m_ctrl.setFullName(*m_arg);
    return true;
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onCMake ()
{
//    if (m_arg == m_argsEnd) {
//    	std::cerr << "Missing arguments\n";
//        return false;
//    }
//
//    std::string arg {*m_arg};
//
//    ++m_arg;
//
//    if (*m_arg == "add") return onCMakeAdd ();
//    else if (*m_arg == "rem") return onCMakeRemove ();
//    else if (*m_arg == "list") return onCMakeList ();
//
//    if (m_arg == m_argsEnd) {
//    	std::cout << "Missing CMake command name.\n";
//    	return false;
//    }
//
//    std::string name {*m_arg};
//
//    ++m_arg;
//    if (m_arg != m_argsEnd) {
//    	std::cerr << "Invalid argument: " << *m_arg << '\n';
//        return false;
//    }
//
//
//    if (!m_ctrl.cmakeExecute(name)) {
//    	std::cerr << "CMake command execute error\n";
//        return false;
//    }
//
    return true;
}
//// -----------------------------------------------------------------------------
//bool MvcViewCliProject::onCMakeAdd ()
//{
//    if (m_arg == m_argsEnd) {
//    	std::cerr << "Missing arguments.\n";
//        return false;
//    }
//    std::string name {*m_arg};
//
//    ++m_arg;
//    if (m_arg == m_argsEnd) {
//    	std::cerr << "Missing arguments.\n";
//        return false;
//    }
//    std::string cmd {*m_arg};
//
//    ++m_arg;
//    if (m_arg != m_argsEnd) {
//    	std::cerr << "Invalid argument: " << *m_arg << '\n';
//        return false;
//    }
//
//    if (!m_ctrl.cmakeAdd(name, cmd)) {
//    	std::cerr << "Add CMake command error.\n";
//        return false;
//    }
//
//    return true;
//}
//// -----------------------------------------------------------------------------
//bool MvcViewCliProject::onCMakeRemove ()
//{
//    if (m_arg == m_argsEnd) {
//    	std::cerr << "Missing arguments.\n";
//        return false;
//    }
//    std::string name {*m_arg};
//    ++m_arg;
//    if (m_arg != m_argsEnd) {
//    	std::cerr << "Invalid argument: " << *m_arg << '\n';
//        return false;
//    }
//
//    if (!m_ctrl.cmakeRemove(name)) {
//    	std::cerr << "Remove CMake command error.\n";
//        return false;
//    }
//
//    return true;
//}
//// -----------------------------------------------------------------------------
//bool MvcViewCliProject::onCMakeList ()
//{
//    if (m_arg != m_argsEnd) {
//    	std::cerr << "Invalid argument: " << *m_arg << '\n';
//        return false;
//    }
//
//    Project::SPtr proj {m_projModel.getProject()};
//    for (auto cmake : proj->getCMakeCmds()) std::cout << cmake.first << " : " << cmake.second << '\n';
//
//    return true;
//}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
