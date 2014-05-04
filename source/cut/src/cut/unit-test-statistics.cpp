#include "stdafx.h"
#include "cut/unit-test-statistics.h"

cut::UnitTestStatistics::UnitTestStatistics( std::size_t groups, std::size_t groupsFailed, std::size_t tests, std::size_t testsFailed ) :
	groups(groups),
	groupsFailed(groupsFailed),
	tests(tests),
	testsFailed(testsFailed)
{
}
