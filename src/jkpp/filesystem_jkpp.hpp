// +++ -------------------------------------------------------------------------
#ifndef FILESYSTEM_JKPP_H
#define FILESYSTEM_JKPP_H
// +++ -------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <string>
// +++ -------------------------------------------------------------------------
namespace jkpp {
// +++ -------------------------------------------------------------------------
boost::filesystem::path getExecDirPath ();
boost::filesystem::path getHomeDirPath ();
bool executeCommand (const std::string& aCommand, std::string& aOutput);
bool executeCommand (const std::string& aCommand);
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
#endif // FILESYSTEM_JKPP_H
#// +++ -------------------------------------------------------------------------
