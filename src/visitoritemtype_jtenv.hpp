// +++ -------------------------------------------------------------------------
#ifndef VISITORITEMTYPE_JTENV_HPP
#define VISITORITEMTYPE_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "visitoritem_jtenv.hpp"

#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class VisitorItemType : public VisitorItem  {
	public:
    	VisitorItemType ();

		virtual void Visit (ItemProject* aItem);
		virtual void Visit (ItemWorkspace* aItem);

        std::string getType () const { return m_type; }

	protected:
    	std::string m_type;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // VISITORITEMTYPE_JTENV_HPP
// +++ -------------------------------------------------------------------------
