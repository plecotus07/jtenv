// +++ -------------------------------------------------------------------------
#include <iostream>
#include "config_jtenv.hpp"
// +++ -------------------------------------------------------------------------
using std::cout;
using std::endl;
using std::string;
// +++ -------------------------------------------------------------------------
void display_help ();
void display_version ();

// +++ -------------------------------------------------------------------------
int main (int aArgc, char* aArgv[])
{
  if ( (aArgc == 1)
       || (string(aArgv[1]) == "-h")
       || (string(aArgv[1]) == "--help"))
    {
      display_help();
      return 0;
    }

  if ( (string(aArgv[1]) == "-v")
       || (string(aArgv[1]) == "--version") )
    {
      display_version();
      return 0;
    }

  return 0;
}
// +++ -------------------------------------------------------------------------
void display_help ()
{
 cout << "  jtpm [-v | --version] [-h | --help] [ADDR] [COMMAND]\n\n";
 cout << "    -v, --version                      - Display version.\n";
 cout << "    -h, --help                         - Display help.\n";
}
// +++ -------------------------------------------------------------------------
void display_version ()
{
  cout << jtenv::GetFullName() << " - v" << jtenv::GetVersion() << endl;
}
// +++ -------------------------------------------------------------------------
