#pragma once

#ifndef CUT_TYPE_TESTMANAGER
#define CUT_TYPE_TESTMANAGER ::cut::DefaultUnitTestManager
#endif

#ifndef CUT_TYPE_LOGMANAGER
#define CUT_TYPE_LOGMANAGER ::cut::DefaultLogManager
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
namespace cut { typedef ::std::function<void()> Lambda_t; }
#endif

#ifndef CUT_TYPE_STRING
#include <string>
#endif
