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
    	using SPtr = std::shared_ptr<Project>;
		using SPtrByStrMap = std::map<std::string, SPtr>;
		using Iterator = SPtrByStrMap::iterator;
        using CMakeCmdsMap = std::map<std::string, std::string>;

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

		virtual bool                 addCMakeCmd (const std::string& aName, const std::string& aCmd);
		virtual bool                 removeCMakeCmd (const std::string& aName);
        virtual std::string          getCMakeCmd (const std::string& aName) const;
        virtual const CMakeCmdsMap&  getCMakeCmds () const { return m_cmakeCmds; }

        virtual void Accept (ItemVisitor& aVisitor) { aVisitor.Visit(this); }

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
