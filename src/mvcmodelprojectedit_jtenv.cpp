// +++ -------------------------------------------------------------------------
#include "mvcmodelprojectedit_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelProjectEdit::MvcModelProjectEdit () :
    MvcModelImpl(),
	m_fullName {},
    m_remoteRepoUrl {},
    m_defaultBranch {}
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
// -----------------------------------------------------------------------------
void MvcModelProjectEdit::setDefaultBranch (const std::string& aBranch)
{
	beginUpdate();
    m_defaultBranch = aBranch;
    endUpdate();
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
