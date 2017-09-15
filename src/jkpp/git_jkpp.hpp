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
		enum class Status { unknown = 0,
		                    clean,
							empty,
                            not_cloned,
                            not_commited,
                            not_pushed};

		virtual ~Git () = default;

		virtual const std::string& getUrl () const = 0;
		virtual void               setUrl (const std::string& aUrl) = 0;

		virtual bool   init (const std::string& aPath, bool aBare) = 0;
		virtual UPtr   clone (const std::string& aPath, bool aBare) = 0;
		virtual Status getStatus (std::string& aStatusDetails) const = 0;

		virtual bool command (const std::string& aCommand) const = 0;

};
// +++ -------------------------------------------------------------------------
class GitBuilder {
	public:
		virtual ~GitBuilder () = default;

        virtual Git::UPtr create (const std::string& aUrl = {}) const = 0;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // GIT_JKPP_HPP
// +++ -------------------------------------------------------------------------
