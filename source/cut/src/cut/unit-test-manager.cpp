#include "cut/unit-test-manager.h"
#include "cut/unit-test-group.h"
#include "cut/common.h"

cut::DefaultUnitTestManager* cut::DefaultUnitTestManager::
	instance()
{
	static DefaultUnitTestManager* instance = nullptr;
	if (instance == nullptr)
	{
		instance = new DefaultUnitTestManager();
	}
	return instance;
}

cut::DefaultUnitTestManager::
	DefaultUnitTestManager() :
	m_statistics(0, 0, 0, 0)
{
}

void cut::DefaultUnitTestManager::
	registerUnitTestGroup(const char* groupName, IUnitTestGroup* testGroup)
{
	m_unitTestGroups[groupName] = testGroup;
	++m_statistics.groups;
}

void cut::DefaultUnitTestManager::
	runAll()
{
	for (auto& groupIter : m_unitTestGroups)
	{
		const char* unitTestGroupName = groupIter.first;
		IUnitTestGroup* unitTestGroup = groupIter.second;
		size_t numberOfTests = unitTestGroup->numberOfUnitTests();

		m_statistics.tests += numberOfTests;

		CUT_LOG(logging::Mode::Normal,
			"\n"
			"Running unit test group %s with %d unit tests:\n",
			unitTestGroupName,
			numberOfTests);
		size_t failed = unitTestGroup->runAllTests();
		if (failed == 0)
		{
			CUT_LOG(cut::logging::Mode::Success,
				"=== Unit test group passed ====================================================\n"
				"Group name: %s\n"
				"Successful unit tests: %d/%d\n"
				"===============================================================================\n",
				unitTestGroupName,
				numberOfTests - failed, numberOfTests);
		}
		else
		{
			++m_statistics.groupsFailed;
			m_statistics.testsFailed += failed;
			CUT_LOG(cut::logging::Mode::Failure,
				"=== Unit test group failed ====================================================\n"
				"Group name: %s\n"
				"Successful unit tests: %d/%d\n"
				"===============================================================================\n",
				unitTestGroupName,
				numberOfTests - failed, numberOfTests);
		}
	}

	const char* finalMessage = "\n"
		"=== Final Statistics ==========================================================\n"
		"Successful unit test groups:	 %d/%d\n"
		"Successful unit tests (total): %d/%d\n";

	if (m_statistics.testsFailed == 0)
	{
		CUT_LOG(cut::logging::Mode::Success,
			finalMessage,
			m_statistics.groups - m_statistics.groupsFailed, m_statistics.groups,
			m_statistics.tests - m_statistics.testsFailed, m_statistics.tests);

		CUT_LOG(cut::logging::Mode::Success,
			"=== All Unit Tests Passed! ====================================================\n");
	}
	else
	{
		CUT_LOG(logging::Mode::Failure,
			finalMessage,
			m_statistics.groups - m_statistics.groupsFailed, m_statistics.groups,
			m_statistics.tests - m_statistics.testsFailed, m_statistics.tests);

		CUT_LOG(cut::logging::Mode::Failure,
			"=== All or Some Unit Tests Failed! ============================================\n");
	}
}

size_t cut::DefaultUnitTestManager::
	numberOfUnitTestGroups()
{
	return m_unitTestGroups.size();
}
