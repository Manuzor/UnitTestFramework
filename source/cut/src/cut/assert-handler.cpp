#include "stdafx.h"
#include "cut/testing/assert-handler.h"
#include "cut-detail/assert-handler.h"

#include "cut/exceptions.h"
#include "cut/testing/unit-test-settings.h"

cut::IAssertHandler* cut::IAssertHandler::s_pInstance = nullptr;

cut::IAssertHandler& cut::IAssertHandler::instance()
{
	static DefaultAssertHandler defaultHandler;

	if(s_pInstance == nullptr)
	{
		s_pInstance = &defaultHandler;
	}

	return *s_pInstance;
}

cut::DefaultAssertHandler::DefaultAssertHandler()
{
}

cut::DefaultAssertHandler::~DefaultAssertHandler()
{
}

void cut::DefaultAssertHandler::handleFailure(const char* file, std::size_t line, StringRef message)
{
	if (settings().doDebugBreaks)
	{
		debugBreak();
	}
	
	throw exceptions::UnitTestFailure(file, line, message);
}

void cut::DefaultAssertHandler::handleSuccess(const char* file, std::size_t line, StringRef message)
{
	throw exceptions::UnitTestSuccess(file, line, message);
}

void cut::DefaultAssertHandler::handleNotImplemented(const char* file, std::size_t line, StringRef message)
{
	throw exceptions::UnitTestNotImplemented(file, line, message);
}
