// +++ -------------------------------------------------------------------------
#include "filesystem_jkpp.hpp"
#include <cstdlib>
#ifdef OS_LINUX
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <linux/limits.h>
#include <unistd.h>
#elif defined OS_MSW
#include <windows.h>
#endif // OS_MSW
#include <boost/process/system.hpp>
#include <boost/process/io.hpp>
#include <boost/filesystem.hpp>
// +++ -------------------------------------------------------------------------
namespace proc = boost::process;
namespace fs = boost::filesystem;
// +++ -------------------------------------------------------------------------
namespace jkpp {
fs::path getExecDirPath ()
{
	std::string result {};
#ifdef OS_LINUX
	char buff[PATH_MAX];
	ssize_t len {readlink("/proc/self/exe", buff, sizeof(buff) - 1)};
	if (len != -1) {
		buff[len] = 0;
		result = buff;
	}
#elif defined OS_MSW
	char buff [MAX_PATH];
	GetModuleFileNameA(nullptr, buff, MAX_PATH);
	result = buff;
#endif // OS_MSW

	return fs::path(result).parent_path();
}
// +++ -------------------------------------------------------------------------
fs::path getHomeDirPath ()
{
	std::string result {};
	char* homedir {};
	homedir = getenv("HOME");
	if (homedir)
		result = homedir;
	else {
#ifdef OS_LINUX
		passwd* pwd {getpwuid(getuid())};
		if (pwd) result = pwd->pw_dir;
#elif defined OS_MSW
		char* homepath {};
		char* homedrive {};

		homepath = getenv("HOMEPATH");
		homedrive = getenv("HOMEDRIVE");

		if (homepath && homedrive) result = std::string{homedrive} + std::string{homepath};
#endif // OS_MSW
	}

	return fs::path(result);
}
// +++ -------------------------------------------------------------------------
bool executeCommand (const std::string& aCommand, std::string& aOutput)
{
	proc::ipstream pipe {};
	int result {0};

	try {
		result = proc::system(aCommand, proc::std_out > pipe);
	} catch (...) {
		result = 1;
	}

    std::string line {};
    while (pipe && std::getline(pipe, line)) {
        aOutput += line + '\n';
    }

    return (result == 0);
}
// +++ -------------------------------------------------------------------------
bool executeCommand (const std::string& aCommand)
{
	int result {0};
	try {
		result = proc::system(aCommand);
	} catch (...) {
		result = 1;
	}

    return (result == 0);
}
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
