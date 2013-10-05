#include "cppunit/UnitTestManager.h"
#include "cppunit/UnitTestGroup.h"
#include "cppunit/Common.h"

cppunit::DefaultUnitTestManager* cppunit::DefaultUnitTestManager::
  instance()
{
  static DefaultUnitTestManager* instance = nullptr;
  if (instance == nullptr)
  {
    instance = new DefaultUnitTestManager();
  }
  return instance;
}

cppunit::DefaultUnitTestManager::
  DefaultUnitTestManager() :
  m_statistics(0, 0, 0, 0)
{
}

void cppunit::DefaultUnitTestManager::
  registerUnitTestGroup(const char* groupName, IUnitTestGroup* testGroup)
{
  m_unitTestGroups[groupName] = testGroup;
  ++m_statistics.groups;
}

void cppunit::DefaultUnitTestManager::
  runAll()
{
  for (auto& groupIter : m_unitTestGroups)
  {
    const char* unitTestGroupName = groupIter.first;
    IUnitTestGroup* unitTestGroup = groupIter.second;
    size_t numberOfTests = unitTestGroup->numberOfUnitTests();

    m_statistics.tests += numberOfTests;

    CPPUNIT_LOG(logging::Mode::Normal, 
      "\n"
      "Running unit test group %s with %d unit tests:\n", 
      unitTestGroupName, 
      numberOfTests);
    size_t failed = unitTestGroup->runAllTests();
    if (failed == 0)
    {
      CPPUNIT_LOG(cppunit::logging::Mode::Success,
        "=== Unit test group passed ====================================================\n"
        "Group name: %s\n"
        "Failed unit tests: %d/%d\n"
        "===============================================================================\n",
        unitTestGroupName,
        failed, numberOfTests);
    }
    else
    {
      ++m_statistics.groupsFailed;
      m_statistics.testsFailed += failed;
      CPPUNIT_LOG(cppunit::logging::Mode::Failure, 
        "=== Unit test group failed ====================================================\n"
        "Group name: %s\n"
        "Failed unit tests: %d/%d\n"
        "===============================================================================\n",
        unitTestGroupName,
        failed, numberOfTests);
    }
  }

  const char* finalMessage = "\n"
    "=== Final Statistics ==========================================================\n"
    "Failed unit test groups:   %d/%d\n"
    "Failed unit tests (total): %d/%d\n";

  if (m_statistics.testsFailed == 0)
  {
    CPPUNIT_LOG(cppunit::logging::Mode::Success, 
      finalMessage,
      m_statistics.groupsFailed, m_statistics.groups,
      m_statistics.testsFailed, m_statistics.tests);

    CPPUNIT_LOG(cppunit::logging::Mode::Success, 
      "=== All Unit Tests Passed! ====================================================\n");
  }
  else
  {
    CPPUNIT_LOG(logging::Mode::Failure, 
      finalMessage,
      m_statistics.groupsFailed, m_statistics.groups,
      m_statistics.testsFailed, m_statistics.tests);

    CPPUNIT_LOG(cppunit::logging::Mode::Failure, 
      "=== All or Some Unit Tests Failed! ============================================\n");
  }
}

size_t cppunit::DefaultUnitTestManager::
  numberOfUnitTestGroups()
{
  return m_unitTestGroups.size();
}
