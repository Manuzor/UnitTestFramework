#pragma once
#include <fstream>
#include <map>
#include <functional>

#ifndef CPPUNIT_TYPE_TESTMANAGER
#define CPPUNIT_TYPE_TESTMANAGER ::cppunit::DefaultUnitTestManager
#endif

#ifndef CPPUNIT_TYPE_LOGMANAGER
#define CPPUNIT_TYPE_LOGMANAGER ::cppunit::logging::DefaultManager
#endif

#ifndef CPPUNIT_TYPE_FILESTREAM
#define CPPUNIT_TYPE_FILESTREAM ::std::ofstream
#endif

#ifndef CPPUNIT_TYPE_MAP
#define CPPUNIT_TYPE_MAP ::std::map
#endif

#ifndef CPPUNIT_TYPE_LAMBDA
#define CPPUNIT_TYPE_LAMBDA ::std::function<void()>
#endif
