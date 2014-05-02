#pragma once
#include "cut/common.h"

namespace cut
{
	namespace assert
	{
		inline void isTrue(bool expr, const char* message = nullptr, ...);
		inline void isFalse(bool expr, const char* message = nullptr, ...);

		template<typename T_Exception>
		inline void throws(_Lambda& lambda, const char* message = nullptr);

		inline void throwsNot(_Lambda& lambda, const char* message = nullptr);

		inline void fail(const char* message = nullptr, ...);
		inline void succeed(const char* message = nullptr, ...);
	};
}

#include "cut/assert.inl"
