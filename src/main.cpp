// +++ -------------------------------------------------------------------------
#include "mvcapp_jtenv.hpp"
// +++ -------------------------------------------------------------------------
int main (int aArgc, char* aArgv[])
{
	jtenv::MvcApp app {};

	std::vector<std::string> args;
	for (int i = 1; i < aArgc; ++i) args.push_back(aArgv[i]);

	return app.run(args);
}
// +++ -------------------------------------------------------------------------
