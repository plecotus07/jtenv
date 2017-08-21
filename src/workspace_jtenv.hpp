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

        Workspace (const std::string& aName, jkpp::Git::UPtr&& aGit, const fs::path& aPath = fs::path());

        virtual bool clone (const std::string& aUserName, const std::string& aUserEmail);

        virtual const std::string& getName () const { return m_name; }
        virtual const fs::path&    getPath () const { return m_path; }
        virtual void               setPath (const fs::path& aPath);
        virtual jkpp::Git&         getGit() { return *(m_git.get()); }

		Project::SPtr              addProject (const std::string& aName, jkpp::Git::UPtr&& aGit);
		Project::SPtr              getProject (const std::string& aName);

        Project::Iterator begin () { return m_projects.begin(); };
        Project::Iterator end () { return m_projects.end(); };

    protected:
    	std::string     m_name;
        fs::path        m_path;
        jkpp::Git::UPtr m_git;

		Project::SPtrByStrMap m_projects;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // WORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
