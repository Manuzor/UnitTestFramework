#include "stdafx.h"
#include "cut/testing/unit-test-settings.h"
#include <string.h>

void processArgument(char* arg)
{
	if(strcmp(arg, "-i") == 0 || strcmp(arg, "--interactive") == 0)
	{
		cut::settings().doDebugBreaks = true;
	}
}

int main(int argc, char* argv[])
{
	// parse settings
	for(int i = 1; i < argc; ++i)
	{
		processArgument(argv[i]);
	}

	cut::IUnitTestManager::instance().runAll();

	system("pause");
	return 0;
}
