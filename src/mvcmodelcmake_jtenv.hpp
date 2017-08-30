// +++ -------------------------------------------------------------------------
#ifndef MVCMODELCMAKE_JTENV_HPP
#define MVCMODELCMAKE_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <mvcmodelimpl_jkpp.hpp>
#include <map>
// +++ -------------------------------------------------------------------------
namespace jtenv {
// +++ -------------------------------------------------------------------------
class MvcModelCMake : public jkpp::MvcModelImpl {
	public:
		MvcModelCMake ();

		const std::string& getConfFilePath () const { return m_confFilePath; }

		std::string getCommand (const std::string& aName);
        bool        addCommand (const std::string& aName, const std::string& aCommand);
        bool        removeCommand (const std::string& aName);

		bool load ();
		bool save ();

	protected:
		const std::string m_confFilePath;
		std::map<std::string, std::string> m_cmakeCmds;

		bool loadLines (std::ifstream& aFile);
};
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // MVCMODELCMAKE_JTENV_HPP
// +++ -------------------------------------------------------------------------
