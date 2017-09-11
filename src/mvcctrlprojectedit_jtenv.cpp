// +++ -------------------------------------------------------------------------
#include "mvcctrlprojectedit_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
MvcCtrlProjectEdit::MvcCtrlProjectEdit (MvcModelProject& aModel, MvcModelItemSelection& aItemSelModel) :
    m_model {aModel},
    m_itemSelModel {aItemSelModel}
{
///\todo assert (m_git != nullptr)
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
