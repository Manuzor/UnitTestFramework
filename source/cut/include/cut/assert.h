#pragma once
#include "cut/common.h"

namespace cut
{
	namespace Assert
	{
		inline void True(bool expr, const char* message = nullptr, ...);
		inline void False(bool expr, const char* message = nullptr, ...);

		template<typename T_Exception>
		inline void Throws(_Lambda& lambda, const char* message = nullptr);

		inline void DoesNotThrow(_Lambda& lambda, const char* message = nullptr);

		inline void Fail(const char* message = nullptr, ...);
		inline void Succeed(const char* message = nullptr, ...);
	};
}

#include "cut/assert.inl"
