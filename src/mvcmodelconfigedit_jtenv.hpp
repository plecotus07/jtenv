// +++ -------------------------------------------------------------------------
#ifndef MVCMODELCONFIGEDIT_JTENV_HPP
#define MVCMODELCONFIGEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcmodelimpl_jkpp.hpp>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfigEdit : public jkpp::MvcModelImpl {
	public:
		MvcModelConfigEdit ();

		const std::string & getUserName () const { return m_userName; }
		void setUserName (const std::string& aUserName);

		const std::string & getUserEmail () const { return m_userEmail; }
		void setUserEmail (const std::string& aUserEmail);

	protected:
		std::string m_userName;
		std::string m_userEmail;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELCONFIGEDIT_JTENV_HPP
// +++ -------------------------------------------------------------------------
