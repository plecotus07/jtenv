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

		virtual const std::string& getPath () const  { return m_path; }

		virtual bool init (const std::string& aPath, bool aBare);
		virtual UPtr clone (const std::string& aPath, bool aBare);
        virtual bool set (const std::string& aPath);

		virtual bool command (const std::string& aCommand) const;

	protected:
		std::string m_path;
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
