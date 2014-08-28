#include "stdafx.h"
#include "cut/testing/unit-test-settings.h"
#include "cut/logging/default-loggers.h"
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

	// Register the desired logging targets.
	auto& logManager = cut::ILogManager::instance();
	cut::loggers::StdOutWriter stdOutLogger(logManager);
	cut::loggers::FileWriter fileLogger(logManager, "unit-tests.log");
	cut::loggers::VisualStudioWriter vsLogger(logManager);

	// Enable or disable some tests or entire groups.
	auto& testManager = cut::IUnitTestManager::instance();

	testManager.disableUnitTestOrGroup("Enable/Disable Groups and Tests", "Disabled1");
	testManager.disableUnitTestOrGroup("Enable/Disable Groups and Tests", "Disabled2");

	testManager.disableUnitTestOrGroup("Disabled Group");

	// Run all unit tests.
	testManager.runAll();

	// Pause before exiting.
	system("pause");
	return 0;
}
