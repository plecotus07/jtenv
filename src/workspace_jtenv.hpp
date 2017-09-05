// +++ -------------------------------------------------------------------------
#ifndef WORKSPACE_JTENV_HPP
#define WORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"
#include "project_jtenv.hpp"

#include <map>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class Workspace : public Item {
    public:
    	using SPtr = std::shared_ptr<Workspace>;
		using SPtrByStrMap = std::map<std::string, SPtr>;
        using Iterator = SPtrByStrMap::iterator;

        Workspace (const std::string& aName, jkpp::Git::UPtr&& aRemoteGit, jkpp::Git::UPtr&& aGit = nullptr);

        virtual bool clone (const std::string& aUserName, const std::string& aUserEmail, const fs::path& aPath = fs::path{});
        virtual bool clear (bool aForce, std::string& aDetails);
        virtual bool git (const std::string& aCommand);

        virtual const std::string& getName () const { return m_name; }
        virtual fs::path           getPath () const { return getRepoPath(); }
		virtual fs::path           getRepoPath () const { return m_git ? m_git->getUrl() : fs::path{}; }
		virtual jkpp::Git::Status  getStatus (std::string& aStatusDetails) const;

        virtual void               Accept (ItemVisitor& aVisitor) { aVisitor.Visit(this); }

		Project::SPtr              addProject (const std::string& aName);
		Project::SPtr              getProject (const std::string& aName);

        Project::Iterator begin () { return m_projects.begin(); };
        Project::Iterator end () { return m_projects.end(); };

    protected:
    	std::string     m_name;
        fs::path        m_path;
        jkpp::Git::UPtr m_remoteGit;
        jkpp::Git::UPtr m_git;

		Project::SPtrByStrMap m_projects;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // WORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
