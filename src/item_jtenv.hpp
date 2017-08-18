// +++ -------------------------------------------------------------------------
#ifndef ITEM_JTENV_HPP
#define ITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <memory>
// +++ -------------------------------------------------------------------------
namespace fs = boost::filesystem;
namespace jtenv {
// +++ -------------------------------------------------------------------------
class Item {
    public:
    	using SPtr = std::shared_ptr<Item>;

		virtual ~Item () = default;

        virtual const std::string& getName () const = 0;

        virtual const fs::path&    getPath () const = 0;
        virtual void               setPath (const fs::path& aPath) = 0;
        virtual fs::path           getRepoPath () const = 0;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // ITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
