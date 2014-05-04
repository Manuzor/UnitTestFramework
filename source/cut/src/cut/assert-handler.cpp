#include "stdafx.h"
#include "cut/assert-handler.h"
#include "cut/exceptions.h"
#include "cut/unit-test-settings.h"

cut::IAssertHandler* cut::IAssertHandler::s_instance = nullptr;

cut::IAssertHandler& cut::IAssertHandler::instance()
{
	static DefaultAssertHandler defaultHandler;

	if(s_instance == nullptr)
	{
		s_instance = &defaultHandler;
	}

	return *s_instance;
}

cut::DefaultAssertHandler::DefaultAssertHandler()
{
}

cut::DefaultAssertHandler::~DefaultAssertHandler()
{
}

void cut::DefaultAssertHandler::handleFailure(const char* file, std::size_t line, StringRef message)
{
	if (g_settings.doDebugBreaks)
	{
		CUT_DEBUG_BREAK;
	}
	
	throw exceptions::UnitTestFailure(file, line, message);
}

void cut::DefaultAssertHandler::handleSuccess(const char* file, std::size_t line, StringRef message)
{
	throw exceptions::UnitTestSuccess(file, line, message);
}
