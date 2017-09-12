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
