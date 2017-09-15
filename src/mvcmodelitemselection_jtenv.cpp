// +++ -------------------------------------------------------------------------
#include "mvcmodelitemselection_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelItemSelection::MvcModelItemSelection () :
    jkpp::MvcModelImpl(),
    m_item {}
{
}
// -----------------------------------------------------------------------------
void MvcModelItemSelection::setItem (Item::SPtr aItem)
{
	beginUpdate();
	m_item = aItem;
    endUpdate();
}
// -----------------------------------------------------------------------------
bool MvcModelItemSelection::clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path& aPath)
{
	if (!m_item) return false;

	beginUpdate();
    bool result {m_item->clone(aUserName, aUserEmail, aPath)};
    endUpdate();

    return result;
}
// -----------------------------------------------------------------------------
bool MvcModelItemSelection::clear (bool aForce, std::string& aDetails)
{
	if (!m_item) return false;

	beginUpdate();
    bool result {m_item->clear(aForce, aDetails)};
    endUpdate();

    return result;
}
// -----------------------------------------------------------------------------
bool MvcModelItemSelection::git (const std::string& aGitCmd)
{
	if (!m_item) return false;

	beginUpdate();
    bool result {m_item->git(aGitCmd)};
    endUpdate();

    return result;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
