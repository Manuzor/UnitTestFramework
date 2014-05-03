#pragma once
#include "cut/types.h"
#include "cut/preprocessor.h"
#include "cut/streams/output-file.h"
#include "cut/logging/logging.h"

namespace cut
{
	typedef CUT_TYPE_LAMBDA _Lambda;

	inline void debugBreak()
	{
		__debugbreak();
	}
}

#define CUT_LOG (::cut::DefaultLogManager::instance().logMessage)
