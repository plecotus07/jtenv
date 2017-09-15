// +++ -------------------------------------------------------------------------
#ifndef MVCMODELIMPL_JKPP_HPP
#define MVCMODELIMPL_JKPP_HPP
// +++ -------------------------------------------------------------------------
#include "mvcmodel_jkpp.hpp"

#include <set>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
class MvcModelImpl : public MvcModel {
	public:
		MvcModelImpl ();

		virtual void attachView (MvcView* aView);
		virtual void detachView (MvcView* aView);

		virtual void beginUpdate () { ++m_updateCount; }
		virtual void endUpdate ();

	private:
		virtual void notify ();

		std::set<MvcView*> m_views;
		int                m_updateCount;
};
// +++ -------------------------------------------------------------------------
class MvcModelUpdateControler {
	public:
    	MvcModelUpdateControler (MvcModel* aModel);
		MvcModelUpdateControler (const MvcModelUpdateControler& aOther) = default;
    	~MvcModelUpdateControler ();

		MvcModelUpdateControler& operator= (const MvcModelUpdateControler& aOther) = default;

    protected:
    	MvcModel* m_model;
};
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // MVCMODELIMPL_JKPP_HPP
// +++ -------------------------------------------------------------------------
