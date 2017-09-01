// +++ -------------------------------------------------------------------------
#ifndef ITEM_JTENV_HPP
#define ITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <git_jkpp.hpp>

#include <boost/filesystem.hpp>
#include <memory>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class ItemVisitor;
// +++ -------------------------------------------------------------------------
class Item {
    public:
    	using SPtr = std::shared_ptr<Item>;

		virtual ~Item () = default;

        virtual bool clone (const fs::path& aPath, const std::string& aUserName, const std::string& aUserEmail) = 0;
        virtual bool clear (bool aForce, std::string& aDetails) = 0;
		virtual bool git(const std::string& aCommand) = 0;

        virtual const std::string& getName () const = 0;
		virtual fs::path           getPath () const = 0;
		virtual fs::path           getRepoPath () const = 0;

		virtual jkpp::Git::Status  getStatus (std::string& aStatusDetails) const = 0;

        virtual Accept (ItemVisitor& aVisitor) = 0;

};
// +++ -------------------------------------------------------------------------
class Workspace;
class Project;
// +++ -------------------------------------------------------------------------
class ItemVisitor {
	public:
    	virtual ~ItemVisitor () = default;

		virtual void Visit (Workspace* aWs) = 0;
		virtual void Visit (Project* aProj) = 0;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
