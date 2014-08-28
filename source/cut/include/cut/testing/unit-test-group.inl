
#include "cut/exceptions.h"
#include "cut/testing/unit-test.h"
#include "cut/testing/unit-test-manager.h"
#include <sstream>

inline
cut::UnitTestGroup::UnitTestGroup(StringRef groupName, Lambda_t initialization, Lambda_t shutdown) :
	m_name(groupName),
	m_numFailedTests(0),
	m_initialization(initialization),
	m_shutdown(shutdown),
	m_unitTests()
{
	IUnitTestManager::instance().registerUnitTestGroup(this);
}

inline
cut::UnitTestGroup::~UnitTestGroup()
{
	m_unitTests.clear();
}

inline
void
cut::UnitTestGroup::registerUnitTest(IUnitTest* unitTest )
{
	m_unitTests.push_back(unitTest);
}

inline
std::size_t
cut::UnitTestGroup::runAllTests()
{
	std::size_t failed = 0;
	if(m_initialization) { m_initialization(); }
	CUT_SCOPE_EXIT{ if(m_shutdown) { m_shutdown(); } };
	
	for (auto unitTest : m_unitTests)
	{
		auto unitTestName = unitTest->getName().cString();

		if(!IUnitTestManager::instance().isUnitTestOrGroupEnabled(getName(), unitTestName))
		{
			logMessage(format(
				"Skipping disabled unit test \"%s\".",
				unitTestName));
			continue;
		}

		try
		{
			LogBlock runSingleTest(format("Test \"%s\"", unitTestName));
			unitTest->run();
		}
		catch (exceptions::UnitTestFailure& failure)
		{
			++failed;

			if (failure.message().empty())
			{
				logFailure(format("%s(%d): Unit test \"%s\" failed.",
				           failure.file(),
				           failure.line(),
				           unitTestName));
			}
			else
			{
				logFailure(format("%s(%d): Unit test \"%s\" failed:",
				           failure.file(),
				           failure.line(),
				           unitTestName));
				logFailure(format("  %s", failure.message().cString()));
			}
		}
		catch (exceptions::UnitTestSuccess& success)
		{
			if(success.message().empty())
			{
				logSuccess(format("%s(%d): Unit test \"%s\" succeeded prematurely.",
				                  success.file(),
				                  success.line(),
				                  unitTestName
				                  ));
			}
			else
			{
				logSuccess(format("%s(%d): Unit test \"%s\" succeeded prematurely:",
				                  success.file(),
				                  success.line(),
				                  unitTestName
				                  ));
				logSuccess(format("  %s", success.message().cString()));
			}
		}
		catch(exceptions::UnitTestNotImplemented& notImplemented)
		{
			IUnitTestManager::instance().statistics().testsNotImplemented++;

			if(notImplemented.message().empty())
			{
				logWarning(format("%s(%d): Unit test \"%s\" is not implemented.",
					notImplemented.file(),
					notImplemented.line(),
					unitTestName
					));
			}
			else
			{
				logWarning(format("%s(%d): Unit test \"%s\" is not implemented:",
					notImplemented.file(),
					notImplemented.line(),
					unitTestName
					));
				logWarning(format("  %s", notImplemented.message().cString()));
			}
		}
		catch (std::exception& ex)
		{
			++failed;
			logFailure(format("Unit test \"%s\" failed due to an unhandled std::exception: %s",
			                  unitTestName,
			                  ex.what()));
		}
		catch (...)
		{
			++failed;
			logFailure(format("Unit test \"%s\" failed due to an unknown exception.", unitTestName));
		}
	}
	return failed;
}

inline
std::size_t
cut::UnitTestGroup::numberOfUnitTests()
{
	return m_unitTests.size();
}

inline
cut::StringRef
cut::UnitTestGroup::getName() const
{
	return m_name;
}
