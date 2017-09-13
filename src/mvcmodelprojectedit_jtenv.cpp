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
	m_cmakeCmds {}
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
bool MvcModelProjectEdit::addCMakeCmd (const std::string& aName, const std::string& aCmd)
{
	if (aName.empty() || aCmd.empty()) return false;

    auto found {m_cmakeCmds.find(aName)};
    if (found != m_cmakeCmds.end()) return false;

	beginUpdate();
	m_cmakeCmds.insert(std::make_pair(aName, aCmd));
	endUpdate();

    return true;
}
// -----------------------------------------------------------------------------
bool MvcModelProjectEdit::removeCMakeCmd (const std::string& aName)
{
	auto found (m_cmakeCmds.find(aName));
    if (found == m_cmakeCmds.end()) return false;

	beginUpdate();
	m_cmakeCmds.erase(found);
	endUpdate();

    return true;

}
// -----------------------------------------------------------------------------
std::string MvcModelProjectEdit::getCMakeCmd (const std::string& aName) const
{
    auto found {m_cmakeCmds.find(aName)};
    if (found != m_cmakeCmds.end()) return std::string{};

    return found->second;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
