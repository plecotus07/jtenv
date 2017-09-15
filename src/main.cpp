// +++ -------------------------------------------------------------------------
#include "mvcapp_jtenv.hpp"
// +++ -------------------------------------------------------------------------
int main (int aArgc, char* aArgv[])
{
	std::vector<std::string> args;
	for (int i = 1; i < aArgc; ++i) args.push_back(aArgv[i]);

	jtenv::MvcApp app {args};

	return app.run() ? 0 : 1;
}
// +++ -------------------------------------------------------------------------
