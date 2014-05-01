#pragma once

namespace cut
{
	struct UnitTestStatistics
	{
		size_t groups;
		size_t groupsFailed;
		size_t tests;
		size_t testsFailed;

		UnitTestStatistics(size_t groups, size_t groupsFailed, size_t tests, size_t testsFailed);
	};
}
