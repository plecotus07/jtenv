// +++ -------------------------------------------------------------------------
#include "itemproject_jtenv.hpp"
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
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
