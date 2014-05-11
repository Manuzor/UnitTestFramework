#include "stdafx.h"
#include "cut-detail/unit-test-manager.h"
#include "cut/testing/unit-test-group.h"
#include "cut/common.h"
#include "cut/string-format.h"

cut::IUnitTestManager* cut::IUnitTestManager::s_pInstance(nullptr);

cut::IUnitTestManager& cut::IUnitTestManager::instance()
{
	static DefaultUnitTestManager default;

	if (s_pInstance == nullptr)
	{
		s_pInstance = &default;
	}

	return *s_pInstance;
}

cut::DefaultUnitTestManager::DefaultUnitTestManager() :
	m_statistics()
{
}

cut::DefaultUnitTestManager::~DefaultUnitTestManager()
{
}

void cut::DefaultUnitTestManager::registerUnitTestGroup(IUnitTestGroup* testGroup)
{
	m_unitTestGroups.push_back(testGroup);
	++m_statistics.groups;
}

void cut::DefaultUnitTestManager::runAll()
{
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

	auto finalMessage = "\n"
		"=== Final Statistics ==========================================================\n"
		"Successful unit test groups:   %d/%d\n"
		"Successful unit tests (total): %d/%d\n";

	if (m_statistics.testsFailed == 0)
	{
		logSuccess(format(finalMessage,
						  m_statistics.groups - m_statistics.groupsFailed, m_statistics.groups,
						  m_statistics.tests - m_statistics.testsFailed, m_statistics.tests));

		logSuccess(format("=== All Unit Tests Passed! ====================================================\n"));
	}
	else
	{
		logFailure(format(finalMessage,
						  m_statistics.groups - m_statistics.groupsFailed, m_statistics.groups,
						  m_statistics.tests - m_statistics.testsFailed, m_statistics.tests));

		logFailure(format("=== All or Some Unit Tests Failed! ============================================\n"));
	}
}

const cut::UnitTestStatistics& cut::DefaultUnitTestManager::statistics() const
{
	return m_statistics;
}

void cut::DefaultUnitTestManager::updateStatistics()
{
	m_statistics.groups = m_unitTestGroups.size();
	m_statistics.testsFailed = 0;

	for (auto group : m_unitTestGroups)
	{
	}
	
}

