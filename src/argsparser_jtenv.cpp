// +++ -------------------------------------------------------------------------
#include "argsparser_jtenv.hpp"
// +++ -------------------------------------------------------------------------
#include "config_jtenv.hpp"
// +++ -------------------------------------------------------------------------
#include <iostream>
// +++ -------------------------------------------------------------------------
namespace jtenv
{
// +++ -------------------------------------------------------------------------
//      ArgsParserC
// -----------------------------------------------------------------------------
ArgsParserC::ArgsParserC (int aArgc, char* aArgv[]) : m_args{},
                                                      m_exeFile{}
{
  m_exeFile = aArgv[0];
  for (int i = 1; i < aArgc; ++i)
  {
    m_args.push_back(aArgv[i]);
  }
}
// -----------------------------------------------------------------------------
bool ArgsParserC::Parse ()
{
  bool displayHelp {m_args.empty()};
  bool displayVersion {false};

  for (auto arg : m_args)
  {
    if ( (arg == "-h")
         || (arg == "--help") )
    {
      displayHelp = true;
      break;
    }
    else if ( (arg == "-v")
              || (arg == "--version") )
    {
      displayVersion = true;
      break;
    }
  }

  if (displayHelp)
  {
    DisplayHelp();
    return true;
  }

  if (displayVersion)
  {
    DisplayVersion();
    return true;
  }

  return true;
}
// -----------------------------------------------------------------------------
void ArgsParserC::DisplayHelp ()
{
 std::cout << "  jtpm [-v | --version] [-h | --help] [ADDR] [COMMAND]\n\n";
 std::cout << "    -v, --version                      - Display version.\n";
 std::cout << "    -h, --help                         - Display help.\n";
}
// -----------------------------------------------------------------------------
void ArgsParserC::DisplayVersion ()
{
  std::cout << jtenv::GetFullName() << " - v" << jtenv::GetVersion() << std::endl;
}
// +++ -------------------------------------------------------------------------
} // jtenv
// +++ -------------------------------------------------------------------------
