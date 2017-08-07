// +++ -------------------------------------------------------------------------
#ifndef ITEM_JTENV_HPP
#define ITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"

#include <boost/filesystem.hpp>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class Item {
	public:
		using UPtr = std::unique_ptr<Item>;
        enum class Status {nexists, ncloned, clear};

        Item (const std::string& aName, const fs::path& aPath, const Config::UPtr& aConfig);

        virtual Status getStatus () const;
        virtual bool   clone () const;
        virtual bool   git (const std::string& aCommand) const;

		virtual fs::path    getPath () const { return m_path; }
		virtual std::string getRepoUrl () const = 0;
        virtual fs::path    getRepoPath () const = 0;

	protected:
        std::string m_name;
    	fs::path    m_path;

    	const Config::UPtr& m_config;

		virtual bool exists () const = 0;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
