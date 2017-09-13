// +++ -------------------------------------------------------------------------
#include "mvcmodelprojectedit_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelProjectEdit::MvcModelProjectEdit () :
    MvcModelImpl(),
	m_fullName {},
    m_remoteRepoUrl {}
{
}
// -----------------------------------------------------------------------------
void MvcModelProjectEdit::setFullName (const std::string& aFullName)
{
	beginUpdate();
    m_fullName = aFullName;
    endUpdate();
}
// -----------------------------------------------------------------------------
void MvcModelProjectEdit::setRemoteRepoUrl (const std::string& aUrl)
{
	beginUpdate();
    m_remoteRepoUrl = aUrl;
    endUpdate();
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
