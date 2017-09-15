// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLCONFIGEDIT_JTENV_HPP
#define MVCCTRLCONFIGEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfigEdit;
class MvcModelConfig;
// +++ -------------------------------------------------------------------------
class MvcCtrlConfigEdit {
	public:
		MvcCtrlConfigEdit (MvcModelConfigEdit& aEditModel, MvcModelConfig& aModel);

        void prepareEdit ();
        bool submitEdit ();

        void setUserName (const std::string& aUserName);
        void setUserEmail (const std::string& aUserEmail);

	protected:
		MvcModelConfigEdit& m_editModel;
		MvcModelConfig&     m_model;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLCONFIGEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
