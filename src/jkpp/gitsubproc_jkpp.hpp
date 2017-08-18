// +++ -------------------------------------------------------------------------
#ifndef GITSUBPROC_JKPP_HPP
#define GITSUBPROC_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include "git_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class GitSubProc : public Git {
	public:
		GitSubProc ();

		virtual bool init (const std::string& aPath, bool aBare);
		virtual UPtr clone (const std::string& aLocalPath, bool aBare);
        virtual bool set (const std::string& aPath);

		virtual bool command (const std::string& aCommand) const;

	protected:
		std::string m_remoteUrl;
		std::string m_localPath;
};
// +++ -------------------------------------------------------------------------
class GitSubProcBuilder : public GitBuilder {
	public:
		virtual Git::UPtr create () const;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // GITSUBPROC_JKPP_HPP
// +++ -------------------------------------------------------------------------
