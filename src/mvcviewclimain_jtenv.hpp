// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIMAIN_JTENV_HPP
#define MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcview_jkpp.hpp>

#include <vector>
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcModelConfig;
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcView {
	public:
		MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel);

		void update () {};
		bool parse (const std::vector<std::string>& aArgs);

	protected:
		MvcCtrlMain&    m_ctrl;
        MvcModelConfig& m_configModel;

		bool onUserName (const std::string& aValue);
		bool onUserEmail (const std::string& aValue);
		bool onWorkspacesDirPath (const std::string& aValue);
		bool onPath (const std::vector<std::string>& aArgs);
		bool onListItems (const std::vector<std::string>& aArgs);

		void displayHelp () const;
		void displayVersion () const;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
