#pragma once
#include "cut/common.h"
#include "cut/exceptions.h"
#include "cut/assert-handler.h"
#include "cut/string-ref.h"

namespace cut
{
	struct Assert
	{
		const char* fileName;
		size_t lineNumber;
		
		Assert(const char* fileName, size_t lineNumber) :
			fileName(fileName),
			lineNumber(lineNumber)
		{
		}

		inline void isTrue(bool expr, StringRef message = nullptr)
		{
			if(!expr)
			{
				IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
			}
		}

		inline void isFalse(bool expr, StringRef message = nullptr)
		{
			if(expr)
			{
				IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
			}
		}

		template<typename T_Exception>
		inline void throws(_Lambda& lambda, StringRef message = nullptr)
		{
			try
			{
				lambda();
				IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
			}
			catch(T_Exception&) { return; }
			catch(...)
			{
				IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
			}
		}

		inline void throwsNothing(_Lambda& lambda, StringRef message = nullptr)
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

		inline void fail(StringRef message = nullptr)
		{
			IAssertHandler::instance().handleFailure(fileName, lineNumber, message);
		}

		inline void succeed(StringRef message = nullptr)
		{
			IAssertHandler::instance().handleSuccess(fileName, lineNumber, message);
		}
	};
}

#define CUT_ASSERT ::cut::Assert(CUT_SOURCE_FILE, CUT_SOURCE_LINE)
