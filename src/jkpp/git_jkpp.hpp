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

		virtual bool init (const std::string& aPath, bool aBare) = 0;
		virtual bool clone (const std::string& aLocalPath, const std::string& aRemoteUrl, bool aBare) = 0;
        virtual bool set (const std::string& aPath) = 0;

		virtual bool command (const std::string& aCommand) const = 0;

};
// +++ -------------------------------------------------------------------------
class GitBuilder {
	public:
    	using UPtr = std::unique_ptr<GitBuilder>;
		virtual ~GitBuilder () = default;

        virtual Git::UPtr create () const = 0;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // GIT_JKPP_HPP
// +++ -------------------------------------------------------------------------
