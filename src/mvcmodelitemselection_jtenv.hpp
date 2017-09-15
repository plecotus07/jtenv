// +++ -------------------------------------------------------------------------
#ifndef MVCMODELITEMSELECTION_JTENV_HPP
#define MVCMODELITEMSELECTION_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"

#include <mvcmodelimpl_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelItemSelection : public jkpp::MvcModelImpl {
	public:
		MvcModelItemSelection ();

		bool clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path& aPath = fs::path{});
		bool clear (bool aForce, std::string& aDetails);
		bool git (const std::string& aGitCmd);

        virtual void       setItem (Item::SPtr aItem);
        virtual Item::SPtr getItem () { return m_item; }

	protected:
    	Item::SPtr m_item;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELITEMSELECTION_JTENV_HPP
// +++ -------------------------------------------------------------------------
