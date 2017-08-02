// +++ -------------------------------------------------------------------------
#ifndef MVCMODEL_JKPP_HPP
#define MVCMODEL_JKPP_HPP
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class MvcView;
// +++ -------------------------------------------------------------------------
class MvcModel {
	public:
		virtual ~MvcModel () = default;

		virtual void attachView (MvcView* aView) = 0;
		virtual void detachView (MvcView* aView) = 0;

	protected:
		virtual void beginUpdate () = 0;
		virtual void endUpdate () = 0;
		virtual void notify () = 0;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // MVCAPP_JKPP_HPP
// +++ -------------------------------------------------------------------------
