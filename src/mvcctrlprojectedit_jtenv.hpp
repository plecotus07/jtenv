// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLPROJECTEDIT_JTENV_HPP
#define MVCCTRLPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelProjectEdit;
class MvcModelItemSelection;
// +++ -------------------------------------------------------------------------
class MvcCtrlProjectEdit {
	public:
		MvcCtrlProjectEdit (MvcModelProjectEdit& aModel, MvcModelItemSelection& aItemSelModel);

        void prepareEdit ();
        bool submitEdit ();


	protected:
	    MvcModelProjectEdit&   m_model;
        MvcModelItemSelection& m_itemSelModel;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
