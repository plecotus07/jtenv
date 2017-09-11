// +++ -------------------------------------------------------------------------
#include "mvcmodelitem_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelItem::MvcModelItem () :
    jkpp::MvcModelImpl()
{
}
// -----------------------------------------------------------------------------
bool MvcModelItem::clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path& aPath)
{
	Item::SPtr item {getItem()};
	if (!item) return false;

	beginUpdate();
    bool result {item->clone(aUserName, aUserEmail, aPath)};
    endUpdate();

    return result;
}
// -----------------------------------------------------------------------------
bool MvcModelItem::clear (bool aForce, std::string& aDetails)
{
	Item::SPtr item {getItem()};
	if (!item) return false;

	beginUpdate();
    bool result {item->clear(aForce, aDetails)};
    endUpdate();

    return result;
}
// -----------------------------------------------------------------------------
bool MvcModelItem::git (const std::string& aGitCmd)
{
	Item::SPtr item {getItem()};
	if (!item) return false;

	beginUpdate();
    bool result {item->git(aGitCmd)};
    endUpdate();

    return result;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
