// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIMAIN_JTENV_HPP
#define MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "mvcviewclihelp_jtenv.hpp"
#include "mvcviewcliversion_jtenv.hpp"

#include <mvcview_jkpp.hpp>

#include <vector>
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcView {
	public:
		MvcViewCliMain (int aArgc, char* aArgv[]);

		void update ();

	protected:
		std::vector<std::string> m_args;

        MvcViewCliHelp           m_helpView;
        MvcViewCliVersion        m_versionView;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
