// +++ -------------------------------------------------------------------------
#ifndef PROJECT_JTENV_HPP
#define PROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"

#include <map>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class Project : public Item {
    public:
        enum class CMakeMode {invalid = 0, conf, build};

    	using SPtr         = std::shared_ptr<Project>;
		using SPtrByStrMap = std::map<std::string, SPtr>;
		using Iterator     = SPtrByStrMap::iterator;
        using CMakeCmd     = std::pair<CMakeMode, std::string>;
        using CMakeCmdsMap = std::map<std::string, CMakeCmd>;

        Project (const std::string& aWsName, const std::string& aName, const fs::path& aPath);

        virtual bool init (const std::string& aFullName, jkpp::Git::UPtr&& aRemoteGit);
		virtual bool load (jkpp::GitBuilder& aGitBuilder);
		virtual bool save ();

        virtual bool clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path& aPath = fs::path {});
        virtual bool clear (bool aForce, std::string& aDetails);
        virtual bool git (const std::string& aCommand);

        virtual const std::string& getName () const { return m_name; }
        virtual fs::path           getPath () const { return m_path; }
        virtual fs::path           getRepoPath () const { return m_git ? m_git->getUrl() : fs::path{}; }
		virtual jkpp::Git::Status  getStatus (std::string& aStatusDetails) const;
        virtual const std::string& getWsName () const { return m_wsName; }

        const std::string&   getFullName () const { return m_fullName; }
		void                 setFullName (const std::string& aFullName) { m_fullName = aFullName; }
        std::string          getRemoteRepoUrl () const { return (m_remoteGit ? m_remoteGit->getUrl() : ""); }
		void                 setRemoteRepoUrl (const std::string& aUrl);
        const std::string&   getDefaultBranch () const { return m_defaultBranch; }
		void                 setDefaultBranch (const std::string& aDefaultBranch) { m_defaultBranch = aDefaultBranch; }


		bool                 addCMakeCmd (const std::string& aName, CMakeMode aMode, const std::string& aCmd);
		bool                 removeCMakeCmd (const std::string& aName);
        CMakeCmd             getCMakeCmd (const std::string& aName) const;
        const CMakeCmdsMap&  getCMakeCmds () const { return m_cmakeCmds; }
        void                 setCMakeCmds (const CMakeCmdsMap& aCMakeCmds) { m_cmakeCmds = aCMakeCmds; }

        virtual void accept (ItemVisitor& aVisitor) { aVisitor.visit(this); }

        static CMakeMode   getCMakeModeFromString (const std::string aString);
        static std::string getStringFromCMakeMode (CMakeMode aMode);

    protected:
		std::string     m_wsName;
    	std::string     m_name;
		std::string     m_fullName;
        fs::path        m_path;
        jkpp::Git::UPtr m_remoteGit;
        jkpp::Git::UPtr m_git;
		std::string     m_defaultBranch;

        CMakeCmdsMap    m_cmakeCmds;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // PROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
