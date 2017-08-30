// +++ -------------------------------------------------------------------------
#ifndef MVCVIEWCLIMAIN_JTENV_HPP
#define MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include "addressparser_jtenv.hpp"

#include <mvcview_jkpp.hpp>

#include <vector>
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcCtrlMain;
class MvcModelConfig;
class MvcModelWorkspaces;
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcView {
	public:
		MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel);

		void update () {};
		bool parse (const std::vector<std::string>& aArgs);

	protected:
    	using ArgIterator = std::vector<std::string>::const_iterator;

		MvcCtrlMain&        m_ctrl;
        MvcModelConfig&     m_configModel;
		MvcModelWorkspaces& m_workspacesModel;
        AddressParser       m_addressParser;

		bool onUserName (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onUserEmail (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onPath (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onInitItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onStatus (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onClone (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onItemClear (ArgIterator& aArg, const ArgIterator& aArgsEnd);

		void displayHelp () const;
		void displayVersion () const;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
