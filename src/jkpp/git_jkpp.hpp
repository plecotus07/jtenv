// +++ -------------------------------------------------------------------------
#ifndef GIT_JKPP_HPP
#define GIT_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include <string>
#include <memory>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class Git {
	public:
    	using UPtr = std::unique_ptr<Git>;
		virtual ~Git () = default;

		virtual const std::string& getPath () const = 0;

		virtual bool init (const std::string& aPath, bool aBare) = 0;
		virtual UPtr clone (const std::string& aPath, bool aBare) = 0;
        virtual void set (const std::string& aPath) = 0;

		virtual bool command (const std::string& aCommand) const = 0;

};
// +++ -------------------------------------------------------------------------
class GitBuilder {
	public:
		virtual ~GitBuilder () = default;

        virtual Git::UPtr create () const = 0;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // GIT_JKPP_HPP
// +++ -------------------------------------------------------------------------
