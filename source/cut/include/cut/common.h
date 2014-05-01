#pragma once
#include "Types.h"
#include "cut/streams/output-file.h"
#include "cut/containers/map.h"
#include "cut/logging/logging.h"

namespace cut
{
	typedef CUT_TYPE_LAMBDA _Lambda;

	inline void debugBreak()
	{
		__debugbreak();
	}
}

#define CUT_LOG (::cut::logging::DefaultManager::instance()->logMessage)
