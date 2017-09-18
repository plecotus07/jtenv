// +++ -------------------------------------------------------------------------
#include "variablesmanager_jtenv.hpp"
#include <iostream>

// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
VariablesManager::VariablesManager () : m_variables{}
{
}
// -----------------------------------------------------------------------------
void VariablesManager::addVariable (const std::string& aName, const std::string& aValue)
{
	if (aName.empty()) throw std::invalid_argument("add_var_name");
	auto found = m_variables.find(aName);
	if (found != m_variables.end()) throw std::invalid_argument("add_var_name_exist");

    m_variables.insert(std::make_pair(aName, aValue));
}
// -----------------------------------------------------------------------------
std::string VariablesManager::getVariable (const std::string& aName) const
{
	auto found = m_variables.find(aName);
	if (found == m_variables.end()) throw std::out_of_range("get_var_not_exists");
    return found->second;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
