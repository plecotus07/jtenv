// +++ -------------------------------------------------------------------------
#ifndef VISITORITEM_JTENV_HPP
#define VISITORITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
namespace jtenv {
class ItemProject;
class ItemWorkspace;
// +++ -------------------------------------------------------------------------
class VisitorItem {
	public:
    	virtual ~VisitorItem () = default;

		virtual void Visit (ItemProject* aItem) = 0;
		virtual void Visit (ItemWorkspace* aItem) = 0;

	protected:
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // VISITORITEM_JTENV_HPP
// +++ -------------------------------------------------------------------------
