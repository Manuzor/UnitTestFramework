#include "stdafx.h"
#include "cut-detail/unit-test-manager.h"
#include "cut/testing/unit-test-group.h"
#include "cut/common.h"
#include "cut/string-format.h"

cut::IUnitTestManager*
cut::IUnitTestManager::s_pInstance = nullptr;

cut::IUnitTestManager&
cut::IUnitTestManager::instance()
{
	static DefaultUnitTestManager default;

	if (s_pInstance == nullptr)
	{
		s_pInstance = &default;
	}

	return *s_pInstance;
}

cut::DefaultUnitTestManager::DefaultUnitTestManager() :
	m_initialize(nullptr),
	m_shutdown(nullptr),
	m_unitTestGroups(),
	m_statistics()
{
}

cut::DefaultUnitTestManager::~DefaultUnitTestManager()
{
	m_unitTestGroups.clear();
}

void
cut::DefaultUnitTestManager::registerUnitTestGroup(IUnitTestGroup* testGroup)
{
	m_unitTestGroups.push_back(testGroup);
	++m_statistics.groups;
}

void
cut::DefaultUnitTestManager::runAll()
{
	if (m_initialize) { m_initialize(); }
	CUT_SCOPE_EXIT{ if(m_shutdown) { m_shutdown(); } };
	
	for(auto& unitTestGroup : m_unitTestGroups)
	{
		const char* unitTestGroupName = unitTestGroup->getName();
		std::size_t numberOfTests = unitTestGroup->numberOfUnitTests();

		m_statistics.tests += numberOfTests;

		logMessage(format(
			"\n"
			"Running unit test group %s with %d unit tests:\n",
			unitTestGroupName,
			numberOfTests));
		std::size_t failed = unitTestGroup->runAllTests();
		if (failed == 0)
		{
			logSuccess(format(
				"=== Unit test group passed ====================================================\n"
				"Group name: %s\n"
				"Successful unit tests: %d/%d\n"
				"===============================================================================\n",
				unitTestGroupName,
				numberOfTests - failed, numberOfTests));
		}
		else
		{
			++m_statistics.groupsFailed;
			m_statistics.testsFailed += failed;
			logFailure(format(
				"=== Unit test group failed ====================================================\n"
				"Group name: %s\n"
				"Successful unit tests: %d/%d\n"
				"===============================================================================\n",
				unitTestGroupName,
				numberOfTests - failed, numberOfTests));
		}
	}

	LogMode loggingMode = m_statistics.testsFailed == 0 ? LogMode::Success : LogMode::Failure;

	log(loggingMode, format("\n"
		" %-16s "           "|"" %6s "   "|"" %9s "      "|"" %6s\n"
		"------------------""+""--------""+""-----------""+""--------\n"
		" %-16s "           "|"" %6u "   "|"" %9u "      "|"" %6u\n"
		" %-16s "           "|"" %6u "   "|"" %9u "      "|"" %6u\n",

		"Final Statistics", "Total",             "Succeeded",                                     "Failed",
		"Test Groups",      m_statistics.groups, m_statistics.groups - m_statistics.groupsFailed, m_statistics.groupsFailed,
		"Tests",            m_statistics.tests,  m_statistics.tests - m_statistics.testsFailed,   m_statistics.testsFailed
		));
}

const cut::UnitTestStatistics&
cut::DefaultUnitTestManager::statistics() const
{
	return m_statistics;
}

void
cut::DefaultUnitTestManager::updateStatistics()
{
	m_statistics.groups = m_unitTestGroups.size();
	m_statistics.testsFailed = 0;

	for (auto group : m_unitTestGroups)
	{
	}
	
}

cut::Lambda_t& cut::DefaultUnitTestManager::initializeFunction()
{
	return m_initialize;
}

cut::Lambda_t& cut::DefaultUnitTestManager::shutdownFunction()
{
	return m_shutdown;
}



