#include "stdafx.h"
#include "cut/unit-test-settings.h"
#include <string.h>

void processArgument(char* arg)
{
	if(strcmp(arg, "-i") == 0 || strcmp(arg, "--interactive") == 0)
	{
		cut::g_settings.doDebugBreaks = true;
	}
}

int main(int argc, char* argv[])
{
	// parse settings
	for(int i = 1; i < argc; ++i)
	{
		processArgument(argv[i]);
	}

	cut::DefaultUnitTestManager::instance().runAll();

	system("pause");
	return 0;
}
