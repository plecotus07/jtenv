// +++ -------------------------------------------------------------------------
#ifndef VARIABLESMANAGER_JTENV_HPP
#define VARIABLESMANAGER_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <map>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class VariablesManager {
	public:
    	using Variable = std::pair<std::string, std::string>;
    	using VariablesMap = std::map<std::string, std::string>;

		VariablesManager ();

        const VariablesMap& getVariables () const { return m_variables; }

        void        addVariable (const std::string& aName, const std::string& aValue);
        std::string getVariable (const std::string& aName) const;

	protected:
        VariablesMap m_variables;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // VARIABLESMANAGER_JTENV_HPP
// +++ -------------------------------------------------------------------------
