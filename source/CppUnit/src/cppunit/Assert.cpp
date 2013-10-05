#include "cppunit/Common.h"
#include "cppunit/Assert.h"
#include "cppunit/exceptions/UnitTestFailure.h"
#include "cppunit/exceptions/UnitTestSuccess.h"

void cppunit::Assert::
  True(bool expr, const char* message /*= nullptr*/, ...)
{
  if (!expr)
  {
    throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
    CPPUNIT_DEBUG_BREAK;
  }
}

void cppunit::Assert::
  False(bool expr, const char* message /*= nullptr*/, ...)
{
  if (expr)
  {
    throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
    CPPUNIT_DEBUG_BREAK;
  }
}

void cppunit::Assert::
  DoesNotThrow(_Lambda& lambda, const char* message /*= nullptr*/)
{
  try
  {
    lambda();
  }
  catch (...)
  {
    throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
    CPPUNIT_DEBUG_BREAK;
  }
}

void cppunit::Assert::Fail(const char* message /*= nullptr*/, ...)
{
  throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
}

void cppunit::Assert::Succeed(const char* message /*= nullptr*/, ...)
{
  throw exceptions::UnitTestSuccess(__FILE__, __LINE__, message);
}
