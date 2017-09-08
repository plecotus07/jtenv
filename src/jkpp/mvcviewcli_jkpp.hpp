// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLI_JKPP_HPP
#define MVCVIEWCLI_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include "mvcview_jkpp.hpp"

#include <vector>
#include <map>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class MvcViewCli : public MvcView {
	public:
    	using ArgIterator = std::vector<std::string>::const_iterator;

		MvcViewCli (ArgIterator& aArg, const ArgIterator& aArgsEnd);

		virtual void show ();
		virtual bool parse () = 0;
		virtual bool containsCommand (const std::string& aCmd) = 0;

		bool getResult () { return m_result; }

	protected:
		ArgIterator m_arg;
		ArgIterator m_argsEnd;
		bool        m_result;

    	template <class T>
		using Handlers = std::map<std::string, bool(*)(T* aView)>;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
