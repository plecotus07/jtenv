// +++ -------------------------------------------------------------------------
#include "itemfactory_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
ItemFactory::ItemFactory (const Config::UPtr& aConfig) : m_config(aConfig)
{
}
// -----------------------------------------------------------------------------
Item::UPtr ItemFactory::Create (const std::string& aAdr)
{
	std::string wsName {};
	std::string projName {};

    if (aArg.empty()) return CreateProject();

    auto pos {aAdr.find_first_of(':')};
    if (pos == std::string::npos) return CreateWorkspace(aAdr);

    return CreateProject(aAdr.substr(0, pos), aAdr.substr(pos + 1));
}
// -----------------------------------------------------------------------------
Item::UPtr ItemFactory::CreateWorkspace (const std::string& aName)
{
///\todo assert(m_config.get() != nullptr)
	std::string wsPath {m_config->getWsPath(aName)};

	return std::make_unique<ItemWorkspace>(aName, aPath, m_config);
}
// -----------------------------------------------------------------------------
Item::UPtr ItemFactory::CreateProject (const std::string& aWsName, const std::string& aName)
{
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
