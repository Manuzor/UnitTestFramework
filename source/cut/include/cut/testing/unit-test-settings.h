#pragma once

namespace cut
{
	struct UnitTestSettings
	{
	public:
		bool doDebugBreaks;

		UnitTestSettings() :
			doDebugBreaks(false)
		{
		}
	};
	
	extern UnitTestSettings g_settings;
}
