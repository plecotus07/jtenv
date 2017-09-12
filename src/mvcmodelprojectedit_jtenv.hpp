// +++ -------------------------------------------------------------------------
#ifndef MVCMODELPROJECTEDIT_JTENV_HPP
#define MVCMODELPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcmodelimpl_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelProjectEdit : public jkpp::MvcModelImpl {
	public:
		MvcModelProjectEdit ();

		const std::string& getFullName () const { return m_fullName; }
		void               setFullName (const std::string& aFullName);

	protected:
		std::string     m_fullName;

};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELPROJECTEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
