// +++ -------------------------------------------------------------------------
#ifndef ITEMFACTORY_JTENV_HPP
#define ITEMFACTORY_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"
#include "item_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class ItemFactory {
	public:
    	ItemFactory (const Config::UPtr& aConfig);

        Item::UPtr Create (const std::string& aAdr);

	protected:
        const Config::UPtr& m_config;

        Item::UPtr CreateProject (const std::string& aWsName = "", const std::string& aName = "");
        Item::UPtr CreateWorkspace (const std::string& aName = "");
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEMFACTORY_JTENV_HPP
// +++ -------------------------------------------------------------------------
