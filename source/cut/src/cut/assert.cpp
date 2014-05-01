#include "cut/common.h"
#include "cut/assert.h"
#include "cut/exceptions/unit-test-failure.h"
#include "cut/exceptions/unit-test-success.h"

void
cut::Assert::True(bool expr, const char* message /*= nullptr*/, ...)
{
  if (!expr)
  {
    throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
    CUT_DEBUG_BREAK;
  }
}

void
cut::Assert::False(bool expr, const char* message /*= nullptr*/, ...)
{
  if (expr)
  {
    throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
    CUT_DEBUG_BREAK;
  }
}

void
cut::Assert::DoesNotThrow(_Lambda& lambda, const char* message /*= nullptr*/)
{
  try
  {
    lambda();
  }
  catch (...)
  {
    throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
    CUT_DEBUG_BREAK;
  }
}

void
cut::Assert::Fail(const char* message /*= nullptr*/, ...)
{
  throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
}

void
cut::Assert::Succeed(const char* message /*= nullptr*/, ...)
{
  throw exceptions::UnitTestSuccess(__FILE__, __LINE__, message);
}
