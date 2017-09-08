// +++ -------------------------------------------------------------------------
#include "mvcctrlconfigedit_jtenv.hpp"

#include "mvcmodelconfigedit_jtenv.hpp"
#include "mvcmodelconfig_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlConfigEdit::MvcCtrlConfigEdit (MvcModelConfigEdit& aEditModel, MvcModelConfig& aModel) :
    m_editModel {aEditModel},
    m_model {aModel}
{
}
// -----------------------------------------------------------------------------
void MvcCtrlConfigEdit::prepareEdit ()
{
    m_editModel.beginUpdate();

	m_editModel.setUserName(m_model.getUserName());
	m_editModel.setUserEmail(m_model.getUserEmail());

    m_editModel.endUpdate();
}
// -----------------------------------------------------------------------------
bool MvcCtrlConfigEdit::submitEdit ()
{
	std::string old_user_name {m_model.getUserName()};
    std::string old_user_email {m_model.getUserEmail()};

    m_model.beginUpdate();

	m_model.setUserName(m_editModel.getUserName());
	m_model.setUserEmail(m_editModel.getUserEmail());

    m_model.endUpdate();

    if (!m_model.save()) {
        m_model.beginUpdate();

		m_model.setUserName(old_user_name);
		m_model.setUserEmail(old_user_email);

	    m_model.endUpdate();

    	return false;
    }

	return true;
}
// -----------------------------------------------------------------------------
void MvcCtrlConfigEdit::setUserName (const std::string& aUserName)
{
    m_editModel.setUserName(aUserName);
}
// -----------------------------------------------------------------------------
void MvcCtrlConfigEdit::setUserEmail (const std::string& aUserEmail)
{
    m_editModel.setUserEmail(aUserEmail);
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
