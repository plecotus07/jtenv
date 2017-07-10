// +++ -------------------------------------------------------------------------
#ifndef _argsparser_jtenv_hpp_
#define _argsparser_jtenv_hpp_
// +++ -------------------------------------------------------------------------
#include <vector>
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv
{
  class ArgsParserC
  {
    public:
      ArgsParserC (int aArgc, char* aArgv[]);

      bool Parse ();

    protected:
      void DisplayHelp ();
      void DisplayVersion ();

      std::vector<std::string> m_args;
      std::string              m_exeFile;

  };
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
#endif // _argsparser_jtenv_hpp_
// +++ -------------------------------------------------------------------------
