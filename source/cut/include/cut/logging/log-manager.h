#pragma once

#include "cppunit/streams/OutputFile.h"
#include "cppunit/logging/Mode.h"

#ifndef CPPUNIT_LOG_FORMATBUFFERSIZE
#define CPPUNIT_LOG_FORMATBUFFERSIZE 1024
#endif // !CPPUNIT_LOG_FORMATBUFFERSIZE

namespace cppunit
{
  namespace logging
  {
    class IManager
    {
    public:
      virtual ~IManager() = 0 {}

      virtual void logMessage(Mode mode, const char* formatString, ...) = 0;
    };

    class DefaultManager : 
      public IManager
    {
    public:

      static DefaultManager* instance();

      DefaultManager();

      virtual ~DefaultManager();

      virtual void logMessage(Mode mode, const char* formatString, ...);

    private:
      void writeToStdOut(Mode mode, const char* formattedString);

      streams::OutputFile m_file;
      char* m_buffer;
    };
  }
}