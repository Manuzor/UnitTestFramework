#include "stdafx.h"
#include "cut/logging/log-manager.h"

using namespace cut;

UnitTestGroup g_group_logBlockTests("LogBlock tests", [](){
	// Initialization code.
	logMessage(">> Level 0 start");
	ILogManager::instance().blockBegin();
}, [](){
	// Shutdown code.
	ILogManager::instance().blockEnd();
	logMessage("<< Level 0 start");
});

UnitTest g_logBlockTests_1(g_group_logBlockTests, "Test Block Levels", [](){
	logMessage("Level 1 start");
	{
		LogBlock block("Block 1");

		logMessage("Level 2 start");
		{
			LogBlock block("Block 2");

			logMessage("Level 3 start");
			{
				LogBlock block("Block 3");

				logMessage("Level 4");
			}
			logMessage("Level 3 end");
		}
		logMessage("Level 2 end");
	}
	logMessage("Level 1 end");
});
