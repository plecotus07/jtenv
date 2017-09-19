// +++ -------------------------------------------------------------------------
#ifndef VARIABLESMANAGER_JTENV_HPP
#define VARIABLESMANAGER_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "variablesmanageriface_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class VariablesManager : public VariablesManagerIface {
	public:
		VariablesManager ();

        virtual const VariablesMap& getVariables () const { return m_variables; }

        virtual void        addVariable (const std::string& aName, const std::string& aValue);
        virtual std::string getVariable (const std::string& aName) const;

		virtual void        addSubManager (SPtr aSubManager);

	protected:
        VariablesMap m_variables;
		SPtr         m_subManager;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // VARIABLESMANAGER_JTENV_HPP
// +++ -------------------------------------------------------------------------
