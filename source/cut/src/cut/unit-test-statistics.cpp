#include "cppunit/UnitTestStatistics.h"

cppunit::UnitTestStatistics::UnitTestStatistics( size_t groups, size_t groupsFailed, size_t tests, size_t testsFailed ) :
  groups(groups),
  groupsFailed(groupsFailed),
  tests(tests),
  testsFailed(testsFailed)
{
}
