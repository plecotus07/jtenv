// +++ -------------------------------------------------------------------------
#ifndef PROJECTCONF_JTENV_HPP
#define PROJECTCONF_JTENV_HPP
// +++ -------------------------------------------------------------------------
#include <boost/filesystem.hpp>
#include <string>
// +++ -------------------------------------------------------------------------
namespace jtenv {
/// Get full name
/// \return Name
std::string getFullName ();
/// Get version.
/// \return Version
std::string getVersion ();
boost::filesystem::path getConfDirPath ();
// +++ -------------------------------------------------------------------------
} /// jtenv
// +++ -------------------------------------------------------------------------
#endif // PROJECTCONF_JTENV_HPP
// +++ -------------------------------------------------------------------------
