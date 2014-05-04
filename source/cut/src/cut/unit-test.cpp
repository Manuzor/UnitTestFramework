#include "stdafx.h"
#include "cut/unit-test.h"
#include "cut/unit-test-group.h"
#include "cut/string-ref.h"


cut::UnitTest::UnitTest(IUnitTestGroup& testGroup, StringRef testName, Lambda_t lambda) :
	m_name(testName),
	m_lambda(lambda)
{
	testGroup.registerUnitTest(this);
}
