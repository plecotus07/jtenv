// +++ -------------------------------------------------------------------------
#ifndef MVCMODELCONFIG_JTENV_HPP
#define MVCMODELCONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcmodelimpl_jkpp.hpp>
#include <boost/filesystem.hpp>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfig : public jkpp::MvcModelImpl {
	public:
		MvcModelConfig ();

		const std::string& getConfFilePath () const { return m_confFilePath; }

		const std::string & getUserName () const { return m_userName; }
		void setUserName (const std::string& aUserName);

		const std::string & getUserEmail () const { return m_userEmail; }
		void setUserEmail (const std::string& aUserEmail);

		const fs::path & getWorkspacesDirPath () const { return m_workspacesDirPath; }
        void setWorkspacesDirPath (const fs::path& aWorkspacesDirPath);

		bool load ();
		bool save ();

	protected:
		const std::string m_confFilePath;

		std::string m_userName;
		std::string m_userEmail;
		fs::path    m_workspacesDirPath;

		bool loadLines (std::ifstream& aFile);
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELCONFIG_JTENV_HPP
// +++ -------------------------------------------------------------------------
