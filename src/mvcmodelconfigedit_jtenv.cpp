// +++ -------------------------------------------------------------------------
#include "mvcmodelconfigedit_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelConfigEdit::MvcModelConfigEdit () :
    jkpp::MvcModelImpl(),
    m_userName {},
    m_userEmail {}
{
}
// -----------------------------------------------------------------------------
void MvcModelConfigEdit::setUserName (const std::string& aUserName)
{
    beginUpdate();
	m_userName = aUserName;
    endUpdate();
}
// -----------------------------------------------------------------------------
void MvcModelConfigEdit::setUserEmail (const std::string& aUserEmail)
{
    beginUpdate();
    m_userEmail = aUserEmail;
    endUpdate();
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
