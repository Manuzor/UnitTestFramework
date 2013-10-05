#pragma once
#include "Types.h"
#include "cppunit/streams/OutputFile.h"
#include "cppunit/containers/Map.h"
#include "cppunit/logging/Logging.h"

#define CPPUNIT_DEBUG_BREAK { __debugbreak(); }

namespace cppunit
{
  typedef CPPUNIT_TYPE_LAMBDA _Lambda;
}

//#define CPPUNIT_LOG ::cppunit::logging::Manager::instance()->logMessage
#define CPPUNIT_LOG ::cppunit::logging::DefaultManager::instance()->logMessage
