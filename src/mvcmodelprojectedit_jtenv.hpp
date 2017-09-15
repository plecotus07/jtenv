// +++ -------------------------------------------------------------------------
#ifndef MVCMODELPROJECTEDIT_JTENV_HPP
#define MVCMODELPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "project_jtenv.hpp"
#include <mvcmodelimpl_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelProjectEdit : public jkpp::MvcModelImpl {
	public:
		MvcModelProjectEdit ();

		const std::string& getFullName () const { return m_fullName; }
		void               setFullName (const std::string& aFullName);
		const std::string& getRemoteRepoUrl () const { return m_remoteRepoUrl; }
		void               setRemoteRepoUrl (const std::string& aUrl);
		const std::string& getDefaultBranch () const { return m_defaultBranch; }
		void               setDefaultBranch (const std::string& aBranch);

		bool                          addCustomCmd (const std::string& aName, const std::string& aDir, const std::string& aCmd);
		bool                          removeCustomCmd (const std::string& aName);
        Project::CustomCmd            getCustomCmd (const std::string& aName) const;
		const Project::CustomCmdsMap& getCustomCmds () const { return m_customCmds; }
		void                          setCustomCmds (const Project::CustomCmdsMap& aCmds) { m_customCmds = aCmds; }

	protected:
		std::string m_fullName;
		std::string m_remoteRepoUrl;
		std::string m_defaultBranch;

		Project::CustomCmdsMap m_customCmds;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
