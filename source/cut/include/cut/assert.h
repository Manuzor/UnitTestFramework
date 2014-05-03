#pragma once
#include "cut/common.h"
#include "cut/exceptions.h"
#include "cut/assert-handler.h"

namespace cut
{
	template<const char* SZ_File, size_t N_Line>
	struct assert
	{
		inline static void isTrue(bool expr, const char* message = nullptr, ...)
		{
			if(!expr)
			{
				IAssertHandler::instance().handleFailure(SZ_File, N_Line, message);
			}
		}

		inline static void isFalse(bool expr, const char* message = nullptr, ...)
		{
			if(expr)
			{
				IAssertHandler::instance().handleFailure(SZ_File, N_Line, message);
			}
		}

		template<typename T_Exception>
		inline static void throws(_Lambda& lambda, const char* message = nullptr)
		{
			try
			{
				lambda();
				IAssertHandler::instance().handleFailure(SZ_File, N_Line, message);
			}
			catch(T_Exception&) { return; }
			catch(...)
			{
				IAssertHandler::instance().handleFailure(SZ_File, N_Line, message);
			}
		}

		inline static void throwsNothing(_Lambda& lambda, const char* message = nullptr)
		{
			try
			{
				lambda();
			}
			catch(...)
			{
				IAssertHandler::instance().handleFailure(SZ_File, N_Line, message);
			}
		}

		inline static void fail(const char* message = nullptr, ...)
		{
			IAssertHandler::instance().handleFailure(SZ_File, N_Line, message);
		}

		inline static void succeed(const char* message = nullptr, ...)
		{
			IAssertHandler::instance().handleSuccess(SZ_File, N_Line, message);
		}
	};
}

#define CUT_ASSERT ::cut::assert<__FILE__, __LINE__>
