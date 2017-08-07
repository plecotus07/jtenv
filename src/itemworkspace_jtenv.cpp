// +++ -------------------------------------------------------------------------
#include "itemworkspace_jtenv.hpp"
#include "visitoritem_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ItemWorkspace::ItemWorkspace (const std::string& aName, const fs::path& aPath, const Config::UPtr& aConfig) :
    Item(aName, aPath, aConfig)
{
}
// -----------------------------------------------------------------------------
std::string ItemWorkspace::getRepoUrl () const
{
///\todo assert(m_config.get() != nullptr)
	if (m_config.get() == nullptr) return std::string();

	return m_config->getWorkspacesUrl() + "/" + m_name + ".git";
}
// -----------------------------------------------------------------------------
bool ItemWorkspace::exists () const
{
    std::string url {getRepoUrl()};

    if (url.empty()) return false;

    if (url.substr(0,6) == "ssh://") {
    } else {
        return fs::exists(url);
    }

    return true;
}
// -----------------------------------------------------------------------------
void ItemWorkspace::Accept (VisitorItem* aVisitor)
{
	///\todo assert(aVisitor 1+ nullptr);
	if (aVisitor == nullptr) return;

	aVisitor->Visit(this);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
