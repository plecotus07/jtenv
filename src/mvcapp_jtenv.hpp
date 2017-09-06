// +++ -------------------------------------------------------------------------
#ifndef MVCAPP_JTENV_HPP
#define MVCAPP_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelworkspace_jtenv.hpp"
#include "mvcmodelproject_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvcviewclicommon_jtenv.hpp"
#include "mvcviewclimain_jtenv.hpp"

#include <mvcapp_jkpp.hpp>
#include <gitsubproc_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcApp : public jkpp::MvcApp {
	public:
		MvcApp ();

		virtual bool run (const std::vector<std::string>& aArgs);

	protected:
		MvcModelConfig 	        m_configModel;
		MvcModelWorkspaces      m_workspacesModel;
		MvcModelWorkspace       m_wsModel;
		MvcModelProject         m_projModel;
		jkpp::GitSubProcBuilder m_gitBuilder;
		MvcCtrlMain             m_mainCtrl;
        MvcViewCliCommon        m_commonView;
		MvcViewCliMain 	        m_mainView;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCAPP_JTENV_HPP
// +++ -------------------------------------------------------------------------
