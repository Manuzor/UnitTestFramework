#pragma once
#include "cut/common.h"
#include "cut/exceptions.h"

namespace cut
{
	template<const char* SZ_File, size_t N_Line>
	struct assert
	{
		inline static void isTrue(bool expr, const char* message = nullptr, ...)
		{
			if(!expr)
			{
				throw exceptions::UnitTestFailure(SZ_File, N_Line, message);
				debugBreak();
			}
		}

		inline static void isFalse(bool expr, const char* message = nullptr, ...)
		{
			if(expr)
			{
				throw exceptions::UnitTestFailure(SZ_File, N_Line, message);
				debugBreak();
			}
		}

		template<typename T_Exception>
		inline static void throws(_Lambda& lambda, const char* message = nullptr)
		{
			try
			{
				lambda();
				throw exceptions::UnitTestFailure(SZ_File, N_Line, message);
			}
			catch(T_Exception&) { return; }
			catch(...) { throw exceptions::UnitTestFailure(SZ_File, N_Line, message); }
		}

		inline static void throwsNothing(_Lambda& lambda, const char* message = nullptr)
		{
			try
			{
				lambda();
			}
			catch(...)
			{
				throw exceptions::UnitTestFailure(SZ_File, N_Line, message);
				debugBreak();
			}
		}

		inline static void fail(const char* message = nullptr, ...)
		{
			throw exceptions::UnitTestFailure(SZ_File, N_Line, message);
		}

		inline static void succeed(const char* message = nullptr, ...)
		{
			throw exceptions::UnitTestSuccess(SZ_File, N_Line, message);
		}
	};
}

#define CUT_ASSERT ::cut::assert<__FILE__, __LINE__>

#include "cut/assert.inl"
