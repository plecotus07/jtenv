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
// +++ -------------------------------------------------------------------------
namespace jkpp {
std::string getExecDirPath ()
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

	return result;
}
// +++ -------------------------------------------------------------------------
std::string getHomeDirPath ()
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

	return result;
}
// +++ -------------------------------------------------------------------------
} // jkpp
// +++ -------------------------------------------------------------------------
