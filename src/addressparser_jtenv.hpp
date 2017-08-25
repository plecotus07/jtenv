// +++ -------------------------------------------------------------------------
#ifndef ADDRESSPARSER_JTENV_HPP
#define ADDRESSPARSER_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"

#include <boost/filesystem.hpp>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class AddressParser {
	public:
		AddressParser (const Workspace::SPtrByStrMap& aWorkspaces);

        std::pair<std::string, std::string> operator () (const std::string& aAddr, const fs::path& aPath = fs::current_path());

	protected:
    	const Workspace::SPtrByStrMap& m_workspaces;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ADDRESSPARSER_JTENV_HPP
// +++ -------------------------------------------------------------------------
