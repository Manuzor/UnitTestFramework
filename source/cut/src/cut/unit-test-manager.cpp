#include "stdafx.h"
#include "cut-detail/unit-test-manager.h"
#include "cut/testing/unit-test-group.h"
#include "cut/common.h"
#include "cut/string-format.h"
#include "cut/logging/log-block.h"

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
	m_statistics(),
	m_disabledUnitTestGroups(),
	m_disabledUnitTests()
{
}

cut::DefaultUnitTestManager::~DefaultUnitTestManager()
{
	m_disabledUnitTests.clear();
	m_disabledUnitTestGroups.clear();
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

	logMessage(format("Framework version " CUT_VERSION_STRING " (%x)", CUT_VERSION));
	
	for(auto& unitTestGroup : m_unitTestGroups)
	{
		const char* unitTestGroupName = unitTestGroup->getName();
		std::size_t numberOfTests = unitTestGroup->numberOfUnitTests();

		m_statistics.tests += numberOfTests;

		if (!isUnitTestOrGroupEnabled(unitTestGroupName))
		{
			logSuccess(format(
				"=== Unit test group skipped ===================================================\n"
				"Group name: %s\n"
				"Skipped unit tests: %d\n"
				"===============================================================================\n",
				unitTestGroupName,
				numberOfTests));
			continue;
		}

		decltype(unitTestGroup->runAllTests()) failed(0);

		{
			LogBlock runGroup("Unit Test Group");
			logMessage(format("Name:  \"%s\".", unitTestGroupName));

			failed = unitTestGroup->runAllTests();
		}

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

	printStats();
}

const cut::UnitTestStatistics&
cut::DefaultUnitTestManager::statistics() const
{
	return m_statistics;
}

cut::UnitTestStatistics&
cut::DefaultUnitTestManager::statistics()
{
	return m_statistics;
}

void
cut::DefaultUnitTestManager::updateStatistics()
{
	m_statistics.groups = m_unitTestGroups.size();
	m_statistics.testsFailed = 0;
}

cut::Lambda_t&
cut::DefaultUnitTestManager::initializeFunction()
{
	return m_initialize;
}

cut::Lambda_t&
cut::DefaultUnitTestManager::shutdownFunction()
{
	return m_shutdown;
}

void
cut::DefaultUnitTestManager::disableUnitTestOrGroup(StringRef groupName)
{
	if (isUnitTestOrGroupEnabled(groupName))
	{
		m_disabledUnitTestGroups.push_back(groupName.cString());
	}
}

void
cut::DefaultUnitTestManager::disableUnitTestOrGroup(StringRef groupName, StringRef testName)
{
	typedef std::pair<std::string, std::string> pair_t;

	if(isUnitTestOrGroupEnabled(groupName, testName))
	{
		m_disabledUnitTests.insert(pair_t(groupName.cString(), testName.cString()));
	}
}

void
cut::DefaultUnitTestManager::enableUnitTestOrGroup(StringRef groupName)
{
	for(auto it = m_disabledUnitTestGroups.cbegin();
		it != m_disabledUnitTestGroups.cend();
		++it)
	{
		if (*it == groupName)
		{
			m_disabledUnitTestGroups.erase(it);
			return;
		}
	}
}

void
cut::DefaultUnitTestManager::enableUnitTestOrGroup(StringRef groupName, StringRef testName)
{
	typedef std::pair<std::string, std::string> pair_t;

	auto stdGroupName = std::string(groupName);
	auto stdTestName = std::string(testName);

	auto range = m_disabledUnitTests.equal_range(stdGroupName);

	for(auto it = range.first;
		it != range.second;
		++it)
	{
		if (it->second == stdTestName)
		{
			m_disabledUnitTests.erase(it);
			return;
		}
	}
}

bool cut::DefaultUnitTestManager::isUnitTestOrGroupEnabled(StringRef groupName)
{
	auto stdGroupName = std::string(groupName.cString());

	for (auto& disabledGroupName : m_disabledUnitTestGroups)
	{
		if(stdGroupName == disabledGroupName)
		{
			return false;
		}
	}

	return true;
}

bool cut::DefaultUnitTestManager::isUnitTestOrGroupEnabled(StringRef groupName, StringRef testName)
{
	auto stdGroupName = std::string(groupName.cString());
	auto stdTestName = std::string(testName.cString());

	// Will be true if the given test is not in the map of disabled unit tests.
	auto range = m_disabledUnitTests.equal_range(stdGroupName);

	auto groupExists = range.first != range.second;

	if (!groupExists)
	{
		// There are no disabled tests for the given group name.
		return true;
	}

	for(auto it = range.first; it != range.second; ++it)
	{
		if(stdTestName == it->second)
		{
			return false;
		}
	}

	return true;
}

void cut::DefaultUnitTestManager::printStats() const
{
	LogMode loggingMode = m_statistics.testsFailed == 0 ? LogMode::Success : LogMode::Failure;

	log(loggingMode, format(
		" %-16s "           "|"" %6s "   "|"" %9s "      "|"" %6s "   "|"" %15s\n"
		"------------------""+""--------""+""-----------""+""--------""+""-----------------\n"
		" %-16s "           "|"" %6u "   "|"" %9u "      "|"" %6u "   "|"" %15s\n"
		" %-16s "           "|"" %6u "   "|"" %9u "      "|"" %6u "   "|"" %15u\n",

		"Final Statistics", "Total", "Succeeded", "Failed", "Not Implemented",
		"Test Groups", m_statistics.groups, m_statistics.groups - m_statistics.groupsFailed, m_statistics.groupsFailed, "",
		"Tests", m_statistics.tests, m_statistics.tests - m_statistics.testsFailed, m_statistics.testsFailed, m_statistics.testsNotImplemented
		));
}
