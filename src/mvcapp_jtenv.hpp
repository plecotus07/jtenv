// +++ -------------------------------------------------------------------------
#ifndef MVCAPP_JTENV_HPP
#define MVCAPP_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "mvcmodelconfig_jtenv.hpp"
#include "mvcmodelworkspaces_jtenv.hpp"
#include "mvcmodelitemselection_jtenv.hpp"
#include "mvcctrlmain_jtenv.hpp"
#include "mvceditorcliconfig_jtenv.hpp"
#include "mvceditorcliitem_jtenv.hpp"
#include "mvcviewclicommon_jtenv.hpp"
#include "mvcviewcliproject_jtenv.hpp"
#include "mvcviewclimain_jtenv.hpp"

#include <mvcapp_jkpp.hpp>
#include <gitsubproc_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcApp : public jkpp::MvcApp {
	public:
		MvcApp (const std::vector<std::string>& aArgs);

		virtual bool run ();

	protected:
		MvcModelConfig 	        m_configModel;
		MvcModelWorkspaces      m_workspacesModel;
		MvcModelItemSelection   m_itemSelModel;
		jkpp::GitSubProcBuilder m_gitBuilder;
		MvcCtrlMain             m_mainCtrl;
		MvcEditorCliConfig      m_configEditor;
		MvcEditorCliItem        m_itemEditor;
        MvcViewCliCommon        m_commonView;
		MvcViewCliMain 	        m_mainView;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCAPP_JTENV_HPP
// +++ -------------------------------------------------------------------------
