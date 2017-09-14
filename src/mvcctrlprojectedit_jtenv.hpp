// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLPROJECTEDIT_JTENV_HPP
#define MVCCTRLPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "mvcmodelprojectedit_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class Project;
class MvcModelProjectEdit;
class MvcModelItemSelection;
// +++ -------------------------------------------------------------------------
class MvcCtrlProjectEdit {
	public:
		MvcCtrlProjectEdit (MvcModelProjectEdit& aEditModel, MvcModelItemSelection& aItemSelModel);

        void prepareEdit (Project* aProject);
        bool submitEdit ();

		void setFullName (const std::string& aFullName) { m_editModel.setFullName(aFullName); }
		void setRemoteRepoUrl (const std::string& aUrl) { m_editModel.setRemoteRepoUrl(aUrl); }
		void setDefaultBranch (const std::string& aBranch) { m_editModel.setDefaultBranch(aBranch); }

		bool addCMakeCmd (const std::string& aName, Project::CMakeMode aMode, const std::string& aCmd) { return m_editModel.addCMakeCmd(aName, aMode, aCmd); };
		bool removeCMakeCmd (const std::string& aName) { return m_editModel.removeCMakeCmd(aName); }
		bool executeCMakeCmd (const std::string& aName);
		bool executeCMakeConfCmd (const std::string& aCmd);
		bool executeCMakeBuildCmd (const std::string& aCmd);

	protected:
		Project*               m_project;
	    MvcModelProjectEdit&   m_editModel;
        MvcModelItemSelection& m_itemSelModel;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
