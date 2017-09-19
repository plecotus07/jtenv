// +++ -------------------------------------------------------------------------
#ifndef VARIABLESMANAGERIFACE_JTENV_HPP
#define VARIABLESMANAGERIFACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <map>
#include <memory>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class VariablesManagerIface {
	public:
    	using Variable     = std::pair<std::string, std::string>;
    	using VariablesMap = std::map<std::string, std::string>;
		using SPtr         = std::shared_ptr<VariablesManagerIface>;

		virtual ~VariablesManagerIface () = default;

        virtual const VariablesMap& getVariables () const = 0;

        virtual void        addVariable (const std::string& aName, const std::string& aValue) = 0;
        virtual std::string getVariable (const std::string& aName) const = 0;

        virtual void        addSubManager (SPtr aSubManager) = 0;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // VARIABLESMANAGERIFACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
