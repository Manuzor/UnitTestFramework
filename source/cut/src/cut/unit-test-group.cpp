#include "stdafx.h"
#include "cut/common.h"
#include "cut/unit-test-group.h"
#include "cut/unit-test-manager.h"
#include "cut/unit-test.h"
#include "cut/exceptions.h"
#include "cut/string-ref.h"

cut::UnitTestGroup::UnitTestGroup(StringRef groupName) :
	m_name(groupName),
	m_numFailedTests(0),
	m_unitTests()
{
	IUnitTestManager::instance().registerUnitTestGroup(this);
}

void
cut::UnitTestGroup::registerUnitTest(IUnitTest* unitTest )
{
	m_unitTests.push_back(unitTest);
}

cut::UnitTestGroup::~UnitTestGroup()
{

}

std::size_t
cut::UnitTestGroup::runAllTests()
{
	std::size_t failed = 0;
	for (auto unitTest : m_unitTests)
	{
		auto unitTestName = unitTest->getName().cString();
		CUT_LOG(LogMode::Normal, "Running unit test %s...\n", unitTestName);
		try
		{
			unitTest->run();
			throw exceptions::UnitTestSuccess();
		}
		catch (exceptions::UnitTestFailure& failure)
		{
			++failed;

			if (failure.message())
			{
				CUT_LOG(LogMode::Failure,
						"Unit test '%s' failed in file %s at line %d:\n  %s\n",
						unitTestName,
						failure.file(),
						failure.line(),
						failure.message().cString());
			}
			else
			{
				CUT_LOG(LogMode::Failure,
						"Unit test '%s' failed in file %s at line %d.",
						unitTestName,
						failure.file(),
						failure.line());
			}
		}
		catch (exceptions::UnitTestSuccess&)
		{
			CUT_LOG(LogMode::Success, "Unit test %s succeeded!\n", unitTestName);
		}
		catch (std::exception& ex)
		{
			++failed;
			CUT_LOG(LogMode::Failure,
				"Unit test %s failed due to an unhandled exception: %s\n",
				unitTestName,
				ex.what()
				);
		}
		catch (...)
		{
			++failed;
			CUT_LOG(LogMode::Failure,
				"Unit test %s failed due to an unknown exception.\n",
				unitTestName
				);
		}
	}
	return failed;
}

std::size_t
cut::UnitTestGroup::numberOfUnitTests()
{
	return m_unitTests.size();
}

cut::StringRef cut::UnitTestGroup::getName() const
{
	return m_name;
}
