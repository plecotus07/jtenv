// +++ -------------------------------------------------------------------------
#ifndef MVCMODELPROJECT_JTENV_HPP
#define MVCMODELPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "project_jtenv.hpp"

#include "mvcmodelitem_jtenv.hpp"
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelProject : public MvcModelItem {
	public:
		MvcModelProject ();

		void          setProject (Project::SPtr aProject);
		Project::SPtr getProject () const { return m_project; }

	protected:
    	Item::SPtr getItem () { return m_project; };

        Project::SPtr m_project;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELPROJECT_JTENV_HPP
// +++ -------------------------------------------------------------------------
