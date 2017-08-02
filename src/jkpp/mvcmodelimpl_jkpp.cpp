// +++ -------------------------------------------------------------------------
#include "mvcmodelimpl_jkpp.hpp"
#include "mvcview_jkpp.hpp"
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
MvcModelImpl::MvcModelImpl () :
    m_views {},
    m_updateCount {0}
{
}
// -----------------------------------------------------------------------------
void MvcModelImpl::attachView (MvcView* aView)
{
	if ( (aView != nullptr)
	        && (m_views.find(aView) == m_views.end()) ) m_views.insert(aView);
}
// -----------------------------------------------------------------------------
void MvcModelImpl::detachView (MvcView* aView)
{
	auto view {m_views.find(aView)};
	if (view != m_views.end()) m_views.erase(view);
}
// -----------------------------------------------------------------------------
void MvcModelImpl::endUpdate ()
{
	--m_updateCount;
	if (m_updateCount == 0) notify();
}
// -----------------------------------------------------------------------------
void MvcModelImpl::notify ()
{
	for (auto view : m_views) view->update();
}
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
