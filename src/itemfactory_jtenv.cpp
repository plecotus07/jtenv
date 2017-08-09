// +++ -------------------------------------------------------------------------
#include "itemfactory_jtenv.hpp"

#include "itemworkspace_jtenv.hpp"
#include "itemproject_jtenv.hpp"
#include <iostream>
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

    if (aAdr.empty()) {
    	if (fs::exists("project.conf")) return CreateProject();
        else return CreateWorkspace();
	}
    auto pos {aAdr.find_first_of(':')};
    if (pos == std::string::npos) return CreateWorkspace(aAdr);

    return CreateProject(aAdr.substr(0, pos), aAdr.substr(pos + 1));
}
// -----------------------------------------------------------------------------
Item::UPtr ItemFactory::CreateWorkspace (const std::string& aName)
{
///\todo assert(m_config.get() != nullptr)
	if (m_config.get() == nullptr) return std::unique_ptr<ItemWorkspace>();

    std::string name {aName};
    if (aName.empty()) name = m_config->getWsName(fs::current_path());

	fs::path wsPath {m_config->getWsPath(name)};

	return std::make_unique<ItemWorkspace>(name, wsPath, m_config);
}
// -----------------------------------------------------------------------------
Item::UPtr ItemFactory::CreateProject (const std::string& aWsName, const std::string& aName)
{
///\todo assert(m_config.get() != nullptr)
	fs::path projPath {};

	if (aName.empty()) {
///\todo   	assert(aWsName.empty())
        for (projPath = fs::current_path(); !fs::exists(projPath / "project.conf") && !projPath.string().empty(); projPath = projPath.parent_path());
    } else {
    	std::string wsName { aWsName };
        if (aWsName.empty()) {
			wsName = m_config->getWsName(fs::current_path());
        }
        if (wsName.empty()) projPath.clear();
        else {
        	fs::path wsPath {m_config->getWsPath(wsName)};
	        if (wsPath.empty()) projPath.clear();
    	    else projPath =  wsPath / aName;
        }
    }

    return std::make_unique<ItemProject>(aWsName, aName, projPath, m_config);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
