// +++ -------------------------------------------------------------------------
#ifndef MVCMODELITEM_JTENV_HPP
#define MVCMODELITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"

#include <mvcmodelimpl_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelItem : public jkpp::MvcModelImpl {
	public:
		MvcModelItem ();

		bool clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path& aPath = fs::path{});
		bool clear (bool aForce, std::string& aDetails);
		bool git (const std::string& aGitCmd);

	protected:
        virtual Item::SPtr getItem () = 0;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
