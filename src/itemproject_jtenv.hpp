// +++ -------------------------------------------------------------------------
#ifndef ITEMPROJECT_JTENV_HPP
#define ITEMPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class ItemProject : public Item {
	public:
        ItemProject (const std::string& aWsName, const std::string& aName, const fs::path& aPath, const Config::UPtr& aConfig);

		virtual std::string getRepoUrl () const { return m_repoUrl; }
        virtual fs::path    getRepoPath () const { return m_path; }

	protected:
		std::string m_wsName;
        std::string m_repoUrl;

		virtual bool exists () const;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEMPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
