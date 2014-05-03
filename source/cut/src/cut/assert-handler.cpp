#include "stdafx.h"
#include "cut/assert-handler.h"

cut::DefaultAssertHandler::DefaultAssertHandler()
{
	if (s_instance == nullptr)
	{
		s_instance = this;
	}
}

cut::DefaultAssertHandler::~DefaultAssertHandler()
{
}

void cut::DefaultAssertHandler::handleFailure(const char* file, size_t line, const char* message)
{
	CUT_DEBUG_BREAK;
	throw exceptions::UnitTestFailure(file, line, message);
}

void cut::DefaultAssertHandler::handleSuccess(const char* file, size_t line, const char* message)
{
	CUT_DEBUG_BREAK;
	throw exceptions::UnitTestSuccess(file, line, message);
}
