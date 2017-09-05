// +++ -------------------------------------------------------------------------
#ifndef MVCMODELWORKSPACE_JTENV_HPP
#define MVCMODELWORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "workspace_jtenv.hpp"

#include "mvcmodelitem_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelWorkspace : public MvcModelItem {
	public:
		MvcModelWorkspace ();

		void            setWorkspace (Workspace::SPtr aWs);
		Workspace::SPtr getWorkspace () const { return m_ws; }

	protected:
    	Item::SPtr getItem () { return m_ws; };

        Workspace::SPtr m_ws;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELWORKSPACE_JTENV_HPP
// +++ -------------------------------------------------------------------------
