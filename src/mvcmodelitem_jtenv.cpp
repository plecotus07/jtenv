// +++ -------------------------------------------------------------------------
#include "mvcmodelitem_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelItem::MvcModelItem () :
    jkpp::MvcModelImpl(),
    m_item{}
{
}
// -----------------------------------------------------------------------------
void MvcModelItem::setItem (Item::SPtr aItem)
{
    beginUpdate();
    m_item = aItem;
    endUpdate();
}
// -----------------------------------------------------------------------------
bool MvcModelItem::clone (const fs::path& aPath, const std::string& aUserName, const std::string& aUserEmail)
{
	if (!m_item) return false;

	beginUpdate();
    bool result {m_item->clone(aPath, aUserName, aUserEmail)};
    endUpdate();

    return result;
}
// -----------------------------------------------------------------------------
bool MvcModelItem::clear (bool aForce, std::string& aDetails)
{
	if (!m_item) return false;

	beginUpdate();
    bool result {m_item->clear(aForce, aDetails)};
    endUpdate();

    return result;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
