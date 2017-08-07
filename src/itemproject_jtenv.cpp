// +++ -------------------------------------------------------------------------
#include "itemproject_jtenv.hpp"
#include "visitoritem_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ItemProject::ItemProject (const std::string& aWsName, const std::string& aName, const fs::path& aPath, const Config::UPtr& aConfig) :
    Item(aName, aPath, aConfig),
    m_wsName {aWsName},
    m_repoUrl {}
{
}
// -----------------------------------------------------------------------------
bool ItemProject::exists () const
{
    std::string url {m_repoUrl};

    if (url.substr(0,6) == "ssh://") {
    } else {
        return fs::exists(url);
    }

    return true;
}
// -----------------------------------------------------------------------------
void ItemProject::Accept (VisitorItem* aVisitor)
{
	///\todo assert(aVisitor 1+ nullptr);
	if (aVisitor == nullptr) return;

	aVisitor->Visit(this);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------