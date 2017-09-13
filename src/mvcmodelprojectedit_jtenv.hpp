// +++ -------------------------------------------------------------------------
#ifndef MVCMODELPROJECTEDIT_JTENV_HPP
#define MVCMODELPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
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

	protected:
		std::string m_fullName;
		std::string m_remoteRepoUrl;
		std::string m_defaultBranch;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
