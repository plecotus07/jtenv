// +++ -------------------------------------------------------------------------
#ifndef MVCVIEW_JKPP_HPP
#define MVCVIEW_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include <memory>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class MvcView {
	public:
    	using UPtr = std::unique_ptr<MvcView>;

    	virtual ~MvcView () = default;

		virtual void show () = 0;
        virtual void update () = 0;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // MVCVIEW_JKPP_HPP
// +++ -------------------------------------------------------------------------
