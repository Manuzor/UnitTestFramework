#include "cut/common.h"
#include "cut/assert.h"
#include "cut/exceptions/unit-test-failure.h"
#include "cut/exceptions/unit-test-success.h"

void
cut::assert::isTrue(bool expr, const char* message /*= nullptr*/, ...)
{
	if (!expr)
	{
		throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
		debugBreak();
	}
}

void
cut::assert::isFalse(bool expr, const char* message /*= nullptr*/, ...)
{
	if (expr)
	{
		throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
		debugBreak();
	}
}

void
cut::assert::throwsNot(_Lambda& lambda, const char* message /*= nullptr*/)
{
	try
	{
		lambda();
	}
	catch (...)
	{
		throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
		debugBreak();
	}
}

void
cut::assert::fail(const char* message /*= nullptr*/, ...)
{
	throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
}

void
cut::assert::succeed(const char* message /*= nullptr*/, ...)
{
	throw exceptions::UnitTestSuccess(__FILE__, __LINE__, message);
}
