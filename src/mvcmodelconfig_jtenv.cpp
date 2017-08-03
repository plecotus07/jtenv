// +++ -------------------------------------------------------------------------
#include "mvcmodelconfig_jtenv.hpp"

#include <filesystem_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelConfig::MvcModelConfig () :
    jkpp::MvcModelImpl(),
    m_config {}
{
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::setUserName (const std::string& aUserName)
{
///\todo assert(m_config.get() != nullptr)
	m_config->setUserName(aUserName);
    return save();
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::setUserEmail (const std::string& aUserEmail)
{
///\todo assert(m_config.get() != nullptr)
	m_config->setUserEmail(aUserEmail);
    return save();
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::setWorkspacesUrl (const std::string& aWorkspacesUrl)
{
///\todo assert(m_config.get() != nullptr)
	m_config->setWorkspacesUrl(aWorkspacesUrl);
    return save();
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::load ()
{
	Config::UPtr config {std::make_unique<Config>(fs::path(jkpp::getHomeDirPath()) / ".jtenv")};
	config->init();
	if (!config->load()) return false;

	m_config = std::move(config);

	return true;
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::save ()
{
///\todo assert(m_config.get() != nullptr)

	return m_config->save();
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
