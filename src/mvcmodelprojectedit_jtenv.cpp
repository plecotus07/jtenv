// +++ -------------------------------------------------------------------------
#include "mvcmodelprojectedit_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcModelProjectEdit::MvcModelProjectEdit () :
    MvcModelImpl(),
	m_fullName {},
    m_remoteRepoUrl {},
    m_defaultBranch {},
	m_customCmds {}
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
// -----------------------------------------------------------------------------
bool MvcModelProjectEdit::addCustomCmd (const std::string& aName, const std::string& aDir, const std::string& aCmd)
{
	if (aName.empty() || aDir.empty() || aCmd.empty()) return false;

    auto found {m_customCmds.find(aName)};
    if (found != m_customCmds.end()) return false;

	beginUpdate();
	m_customCmds.insert(std::make_pair(aName, std::make_pair(aDir, aCmd)));
	endUpdate();

    return true;
}
// -----------------------------------------------------------------------------
bool MvcModelProjectEdit::removeCustomCmd (const std::string& aName)
{
	auto found (m_customCmds.find(aName));
    if (found == m_customCmds.end()) return false;

	beginUpdate();
	m_customCmds.erase(found);
	endUpdate();

    return true;

}
// -----------------------------------------------------------------------------
Project::CustomCmd MvcModelProjectEdit::getCustomCmd (const std::string& aName) const
{
    auto found {m_customCmds.find(aName)};
    if (found == m_customCmds.end()) return std::make_pair(std::string{}, std::string{});

    return found->second;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
