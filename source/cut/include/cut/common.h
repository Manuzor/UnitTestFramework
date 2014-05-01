#pragma once
#include "Types.h"
#include "cut/streams/output-file.h"
#include "cut/containers/map.h"
#include "cut/logging/logging.h"

#define CUT_DEBUG_BREAK { __debugbreak(); }

namespace cut
{
	typedef CUT_TYPE_LAMBDA _Lambda;
}

//#define CUT_LOG ::cut::logging::Manager::instance()->logMessage
#define CUT_LOG (::cut::logging::DefaultManager::instance()->logMessage)
