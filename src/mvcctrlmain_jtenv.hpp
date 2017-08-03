// +++ -------------------------------------------------------------------------
#ifndef MVCCTRLMAIN_JTENV_HPP
#define MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelConfig;
// +++ -------------------------------------------------------------------------
class MvcCtrlMain {
	public:
		MvcCtrlMain (MvcModelConfig& aConfigModel);

		bool loadConfig ();
        bool setUserName (const std::string& aUserName);
        bool setUserEmail (const std::string& aUserEmail);
        bool setWorkspacesUrl (const std::string& aWorkspacesUrl);

	protected:
		MvcModelConfig& m_configModel;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCCTRLMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
