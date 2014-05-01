#include "cut/unit-test-statistics.h"

cut::UnitTestStatistics::UnitTestStatistics( size_t groups, size_t groupsFailed, size_t tests, size_t testsFailed ) :
  groups(groups),
  groupsFailed(groupsFailed),
  tests(tests),
  testsFailed(testsFailed)
{
}
