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

        Project (const std::string& aWsName, const std::string& aName, const fs::path& aPath);

		virtual bool init (const std::string& aFullName, const std::string& aRepoUrl, jkpp::GitBuilder& aGitBuider);
		virtual bool load (jkpp::GitBuilder& aGitBuilder);
		virtual bool save ();
        virtual bool clone (const std::string& aUserName, const std::string& aUserEmail);
        virtual bool git (const std::string& aCommand);

        virtual const std::string& getName () const { return m_name; }
        virtual const fs::path&    getPath () const { return m_path; }
        virtual void               setPath (const fs::path& aPath) { m_path = aPath; }
		virtual jkpp::Git::Status  getStatus (std::string& aStatusDetails) const;
        virtual const std::string& getWsName () const { return m_wsName; }

		virtual bool isCloned () const { return m_git != nullptr; }

    protected:
		std::string     m_wsName;
    	std::string     m_name;
		std::string     m_fullName;
        fs::path        m_path;
        jkpp::Git::UPtr m_git;
        jkpp::Git::UPtr m_remoteGit;
		std::string     m_defaultBranch;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // PROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
