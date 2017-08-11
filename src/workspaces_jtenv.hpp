// +++ -------------------------------------------------------------------------
#ifndef WORKSPACES_JTENV_HPP
#define WORKSPACES_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"
#include "itemworkspace_jtenv.hpp"

#include <git_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class Workspaces {
	public:
    	using WorkspaceByStringMap = std::map<std::string, ItemWorkspace::SPtr>;

    	Workspaces (const Config::UPtr& aConfig, const jkpp::GitBuilder& aGitBuilder);

        ItemWorkspace* getWorkspace (const std::string& aName);
        bool           initWorkspace (const std::string& aName, const fs::path& aLocalDirPath);


	protected:
    	WorkspaceByStringMap    m_workspaces;

        const Config::UPtr&     m_config;
        const jkpp::GitBuilder& m_gitBuilder;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEMFACTORY_JTENV_HPP
// +++ -------------------------------------------------------------------------
