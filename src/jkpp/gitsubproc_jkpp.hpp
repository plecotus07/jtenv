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
		GitSubProc (const std::string& aUrl = {});

		virtual const std::string& getUrl () const  { return m_url; }
		virtual void               setUrl (const std::string& aUrl) { m_url = aUrl; }

		virtual bool   init (const std::string& aUrl, bool aBare);
		virtual UPtr   clone (const std::string& aUrl, bool aBare);

		virtual Status getStatus (std::string& aStatusDetails) const;

		virtual bool   command (const std::string& aCommand) const;

	protected:
		std::string m_url;
};
// +++ -------------------------------------------------------------------------
class GitSubProcBuilder : public GitBuilder {
	public:
		virtual Git::UPtr create (const std::string& aUrl = {}) const;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // GITSUBPROC_JKPP_HPP
// +++ -------------------------------------------------------------------------
