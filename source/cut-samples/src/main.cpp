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

	auto& testManager = cut::IUnitTestManager::instance();

	testManager.disableUnitTestOrGroup("Enable/Disable Groups and Tests", "Disabled1");
	testManager.disableUnitTestOrGroup("Enable/Disable Groups and Tests", "Disabled2");

	testManager.disableUnitTestOrGroup("Disabled Group");

	testManager.runAll();

	system("pause");
	return 0;
}
