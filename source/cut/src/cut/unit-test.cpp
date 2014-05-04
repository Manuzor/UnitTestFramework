#include "stdafx.h"
#include "cut/unit-test.h"
#include "cut/unit-test-group.h"


cut::UnitTest::UnitTest(IUnitTestGroup& testGroup, const char* testName, Lambda_t lambda) :
m_name(testName),
m_lambda(lambda)
{
	testGroup.registerUnitTest(this);
}
