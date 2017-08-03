// +++ -------------------------------------------------------------------------
#ifndef MVCMODELCONFIG_JTENV_HPP
#define MVCMODELCONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcmodelimpl_jkpp.hpp>
#include <config_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfig : public jkpp::MvcModelImpl {
	public:
		MvcModelConfig ();

		const jkpp::Config::UPtr& getConfig () const { return m_config; };

		void setUserName (const std::string& aUserName);

		bool load ();
		bool save ();

	protected:
		jkpp::Config::UPtr m_config;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELCONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
