#pragma once

#ifndef CUT_TYPE_TESTMANAGER
#define CUT_TYPE_TESTMANAGER ::cut::DefaultUnitTestManager
#endif

#ifndef CUT_TYPE_LOGMANAGER
#define CUT_TYPE_LOGMANAGER ::cut::logging::DefaultManager
#endif

#ifndef CUT_TYPE_FILESTREAM
#include <fstream>
#define CUT_TYPE_FILESTREAM ::std::ofstream
#endif

#ifndef CUT_TYPE_MAP
#include <map>
#define CUT_TYPE_MAP ::std::map
#endif

#ifndef CUT_TYPE_LAMBDA
#include <functional>
#define CUT_TYPE_LAMBDA ::std::function<void()>
#endif
