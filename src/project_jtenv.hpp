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

        Project (const std::string& aWsName, const std::string& aName, jkpp::Git::UPtr&& aGit, const fs::path& aPath = fs::path());

        virtual bool clone (const std::string& aUserName, const std::string& aUserEmail);

        virtual const std::string& getName () const { return m_name; }
        virtual const fs::path&    getPath () const { return m_path; }
        virtual void               setPath (const fs::path& aPath) { m_path = aPath; }
        virtual const std::string& getWsName () const { return m_wsName; }
        virtual jkpp::Git&         getGit() { return *(m_git.get()); }

    protected:
		std::string     m_wsName;
    	std::string     m_name;
        fs::path        m_path;
        jkpp::Git::UPtr m_git;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // PROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
