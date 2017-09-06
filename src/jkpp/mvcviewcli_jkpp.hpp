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

		virtual bool parse (ArgIterator& aArg, const ArgIterator aArgsEnd) = 0;
		virtual bool containsCommand (const std::string& aCmd) = 0;

	protected:
    	template <class T>
		using Handlers = std::map<std::string, bool(*)(T* aView, ArgIterator& aArg, const ArgIterator& aArgsEnd)>;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
