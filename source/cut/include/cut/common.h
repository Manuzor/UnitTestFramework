#pragma once
#include "cut/types.h"
#include "cut/preprocessor.h"
#include "cut/streams/output-file.h"
#include "cut/logging/logging.h"

namespace cut
{
	inline void debugBreak()
	{
		__debugbreak();
	}
}
