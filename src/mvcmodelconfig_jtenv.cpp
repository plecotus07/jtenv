// +++ -------------------------------------------------------------------------
#include "mvcmodelconfig_jtenv.hpp"
#include "config_jtenv.hpp"

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
bool MvcModelConfig::load ()
{
	jkpp::Config::UPtr config {std::make_unique<Config>(fs::path(jkpp::getHomeDirPath()) / ".jtenv")};
	config->init();
	if (!config->load()) return false;

	m_config = std::move(config);

	return true;
}
// -----------------------------------------------------------------------------
bool MvcModelConfig::save ()
{
	return true;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
