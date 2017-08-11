// +++ -------------------------------------------------------------------------
#ifndef FILESYSTEM_JKPP_H
#define FILESYSTEM_JKPP_H
// +++ -------------------------------------------------------------------------
#include <string>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
std::string getExecDirPath ();
std::string getHomeDirPath ();
bool executeCommand (const std::string& aCommand, std::string& aOutput);
bool executeCommand (const std::string& aCommand);
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // FILESYSTEM_JKPP_H
#// +++ -------------------------------------------------------------------------
