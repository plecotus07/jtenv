// +++ -------------------------------------------------------------------------
#ifndef MVCAPP_JTENV_HPP
#define MVCAPP_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "mvcviewclimain_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelitem_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"

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
		MvcModelItem            m_itemModel;
		MvcViewCliMain 	        m_mainView;
        jkpp::GitSubProcBuilder m_gitBuilder;
		MvcCtrlMain             m_mainCtrl;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCAPP_JTENV_HPP
// +++ -------------------------------------------------------------------------
