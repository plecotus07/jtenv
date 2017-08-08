// +++ -------------------------------------------------------------------------
#ifndef MVCMODELCONFIG_JTENV_HPP
#define MVCMODELCONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcmodelimpl_jkpp.hpp>
#include <config_jtenv.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfig : public jkpp::MvcModelImpl {
	public:
		MvcModelConfig ();

		const Config::UPtr& getConfig () const { return m_config; };

		bool setUserName (const std::string& aUserName);
		bool setUserEmail (const std::string& aUserEmail);
        bool setWorkspacesDirPath (const fs::path& aWorkspacesDirPath);

		bool load ();
		bool save ();

	protected:
		Config::UPtr m_config;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELCONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
