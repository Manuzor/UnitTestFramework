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
	
	inline UnitTestSettings& settings()
	{
		static UnitTestSettings instance;
		return instance;
	}
}
