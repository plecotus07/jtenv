// +++ -------------------------------------------------------------------------
#ifndef ITEMWORKSPACE_JTENV_HPP
#define ITEMWORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class ItemWorkspace : public Item {
	public:
        ItemWorkspace (const std::string& aName, const fs::path& aPath, const Config::UPtr& aConfig);

		virtual std::string getRepoUrl () const;
        virtual fs::path    getRepoPath () const { return m_path; }

	protected:

		virtual bool exists () const;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEMWORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
