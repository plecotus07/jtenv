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
class MvcModelItem;
// +++ -------------------------------------------------------------------------
class MvcViewCliMain : public jkpp::MvcView {
	public:
		MvcViewCliMain (MvcCtrlMain& aCtrl, MvcModelConfig& aConfigModel, MvcModelWorkspaces& aWorkspacesModel, MvcModelItem& aItemModel);

		void update () {};
		bool parse (const std::vector<std::string>& aArgs);

	protected:
    	using ArgIterator = std::vector<std::string>::const_iterator;

		MvcCtrlMain&        m_ctrl;
        MvcModelConfig&     m_configModel;
		MvcModelWorkspaces& m_workspacesModel;
		MvcModelItem&       m_itemModel;
        AddressParser       m_addressParser;

		bool onUserName (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onUserEmail (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onPath (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onListItems (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onInitItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onStatusItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCloneItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onClearItem (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onGit (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMake (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeAdd (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeRemove (ArgIterator& aArg, const ArgIterator& aArgsEnd);
		bool onCMakeList (ArgIterator& aArg, const ArgIterator& aArgsEnd);

		void displayHelp () const;
		void displayVersion () const;

		using Handlers = std::map<std::string, bool (MvcViewCliMain::*)(ArgIterator& aArg, const ArgIterator& aArgsEnd)>;
		const Handlers m_handlers;

};
// +++ -------------------------------------------------------------------------
class ProjectsLister : public ItemVisitor {
	public:
		ProjectsLister (bool aCloneOnly, bool aWithPath);

		virtual void Visit (Workspace* aWs);
		virtual void Visit (Project* aProj);

	protected:
    	bool m_clonedOnly;
		bool m_withPath;
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCVIEWCLIMAIN_JTENV_HPP
// +++ -------------------------------------------------------------------------
