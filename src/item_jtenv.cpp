// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
Item::Item (const std::string& aName, const fs::path& aPath, const Config::UPtr& aConfig) :
    m_name{aName},
    m_path{aPath},
    m_config{aConfig}
{
}
// -----------------------------------------------------------------------------
Item::Status Item::getStatus () const
{
	if (!exists()) return Status::nexists;

	if (!fs::exists(getRepoPath())) return Status::ncloned;

	return Status::clear;
}
// -----------------------------------------------------------------------------
bool Item::clone () const
{
	return true;
}
// -----------------------------------------------------------------------------
bool Item::git (const std::string& aCommand) const
{

	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
