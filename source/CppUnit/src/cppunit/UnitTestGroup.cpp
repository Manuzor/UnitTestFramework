#include "cppunit/Common.h"
#include "cppunit/UnitTestGroup.h"
#include "cppunit/UnitTestManager.h"
#include "cppunit/UnitTest.h"
#include "cppunit/exceptions/UnitTestSuccess.h"
#include "cppunit/exceptions/UnitTestFailure.h"

cppunit::UnitTestGroup::
  UnitTestGroup(const char* groupName)
{
  TestManager::instance()->registerUnitTestGroup(groupName, this);
}

void cppunit::UnitTestGroup::
  registerUnitTest( const char* unitTestName, IUnitTest* unitTest )
{
  m_unitTests[unitTestName] = unitTest;
}

cppunit::UnitTestGroup::
  ~UnitTestGroup()
{

}

unsigned int cppunit::UnitTestGroup::
  runAllTests()
{
  unsigned int failed = 0;
  for (auto& unitTestIterator : m_unitTests)
  {
    const char* unitTestName = unitTestIterator.first;
    IUnitTest* unitTest = unitTestIterator.second;
    CPPUNIT_LOG(logging::Mode::Normal, "Running unit test %s...\n", unitTestName);
    try
    {
      unitTest->run();
      throw exceptions::UnitTestSuccess();
    }
    catch (const exceptions::UnitTestFailure& failure)
    {
      ++failed;

      if (failure.message() == nullptr)
      {
        CPPUNIT_LOG(logging::Mode::Failure, 
          "Unit test %s failed in file %s at line %d.\n", 
          unitTestName, 
          failure.file(), 
          failure.line()
          );
      }
      else
      {
        CPPUNIT_LOG(logging::Mode::Failure, 
          "Unit test %s failed in file %s at line %d:\n  %s\n", 
          unitTestName, 
          failure.file(), 
          failure.line(), 
          failure.message()
          );
      }
    }
    catch (const exceptions::UnitTestSuccess&)
    {
      CPPUNIT_LOG(logging::Mode::Success, "Unit test %s succeeded!\n", unitTestName);
    }
    catch (...)
    {
      ++failed;
      CPPUNIT_LOG(logging::Mode::Failure, 
        "Unit test %s failed with an unhandled exception.\n",
        unitTestName
        );
    }
  }
  return failed;
}

size_t cppunit::UnitTestGroup::
  numberOfUnitTests()
{
  return m_unitTests.size();
}
