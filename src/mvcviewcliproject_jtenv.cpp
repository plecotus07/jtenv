// +++ -------------------------------------------------------------------------
#include "mvcviewcliproject_jtenv.hpp"

#include "mvcctrlmain_jtenv.hpp"
#include "mvcmodelproject_jtenv.hpp"

#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcViewCliProject::MvcViewCliProject (MvcCtrlMain& aCtrl, MvcModelProject& aProjModel) :
    m_ctrl {aCtrl},
    m_projModel {aProjModel},
    m_handlers {{"cmake", [] (MvcViewCliProject* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd) -> bool {return aView->onCMake(aArg, aArgsEnd);}}}
{
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::parse (ArgIterator& aArg, const ArgIterator aArgsEnd)
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
bool MvcViewCliProject::containsCommand (const std::string& aCmd)
{
    return (m_handlers.find(aCmd) != m_handlers.end());
}
// -----------------------------------------------------------------------------
bool MvcViewCliProject::onCMake (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg == aArgsEnd) {
    	std::cerr << "Missing arguments\n";
        return false;
    }

    if (*aArg == "add") return onCMakeAdd (++aArg, aArgsEnd);
    else if (*aArg == "rem") return onCMakeRemove (++aArg, aArgsEnd);
    else if (*aArg == "list") return onCMakeList (++aArg, aArgsEnd);

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
bool MvcViewCliProject::onCMakeAdd (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
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
bool MvcViewCliProject::onCMakeRemove (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
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
bool MvcViewCliProject::onCMakeList (ArgIterator& aArg, const ArgIterator& aArgsEnd)
{
    if (aArg != aArgsEnd) {
    	std::cerr << "Invalid argument: " << *aArg << '\n';
        return false;
    }

    Project::SPtr proj {m_projModel.getProject()};
    for (auto cmake : proj->getCMakeCmds()) std::cout << cmake.first << " : " << cmake.second << '\n';

    return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
