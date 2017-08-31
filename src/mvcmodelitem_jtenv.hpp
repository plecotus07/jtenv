// +++ -------------------------------------------------------------------------
#ifndef MVCMODELITEM_JTENV_HPP
#define MVCMODELITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "item_jtenv.hpp"

#include <mvcmodelimpl_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelItem : public jkpp::MvcModelImpl {
	public:
		MvcModelItem ();

		void       setItem (Item::SPtr aItem);
		Item::SPtr getItem () const { return m_item; }

	protected:
        Item::SPtr m_item;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
