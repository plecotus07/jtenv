// +++ -------------------------------------------------------------------------
#include "visitoritemtype_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
VisitorItemType::VisitorItemType () :
    m_type{}
{
}
// -----------------------------------------------------------------------------
void VisitorItemType::Visit (ItemProject* aItem)
{
    m_type = "project";
}
// -----------------------------------------------------------------------------
void VisitorItemType::Visit (ItemWorkspace* aItem)
{
    m_type = "workspace";
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------