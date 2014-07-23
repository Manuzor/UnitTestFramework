#include "stdafx.h"
#include "cut/testing/assert.h"
#include "cut/testing/assert-handler.h"

cut::Assert::Assert(const char* fileName, std::size_t lineNumber) :
fileName(fileName),
lineNumber(lineNumber)
{

}

void cut::Assert::isTrue(bool expr, StringRef message /*= nullptr*/)
{
	if(!expr)
	{
		IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
	}
}

void cut::Assert::isFalse(bool expr, StringRef message /*= nullptr*/)
{
	if(expr)
	{
		IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
	}
}

void cut::Assert::throwsNothing(Lambda_t lambda, StringRef message /*= nullptr*/)
{
	try
	{
		lambda();
	}
	catch(...)
	{
		IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
	}
}

void cut::Assert::fail(StringRef message /*= nullptr*/)
{
	IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
}

void cut::Assert::succeed(StringRef message /*= nullptr*/)
{
	IAssertHandler::instance().handleSuccess(fileName, lineNumber, message);
}
