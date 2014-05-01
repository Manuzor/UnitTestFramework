#include "cut/logging/log-manager.h"
#include <cstdarg>
#include <windows.h>

#ifndef CUT_LOGFILENAME
#define CUT_LOGFILENAME "UnitTest.log"
#endif // !CUT_LOGFILENAME

cut::logging::DefaultManager* cut::logging::DefaultManager::
  instance()
{
  static DefaultManager* instance;
  if (instance == nullptr)
  {
    instance = new DefaultManager();
  }
  return instance;
}

cut::logging::DefaultManager::
  DefaultManager() :
  m_file(CUT_LOGFILENAME)
{
  m_buffer = new char[CUT_LOG_FORMATBUFFERSIZE];
}

cut::logging::DefaultManager::
  ~DefaultManager()
{
  delete[] m_buffer;
  m_buffer = nullptr;
}

void cut::logging::DefaultManager::
  logMessage(Mode mode, const char* formatString, ...)
{
  va_list args;
  va_start(args, formatString);
  try
  {
    //TODO: Check if vsnprintf is MSC specific.
#pragma warning(suppress : 4996)
    vsnprintf(m_buffer, CUT_LOG_FORMATBUFFERSIZE - 1, formatString, args);
  }
  catch (...)
  {
    printf("ERROR! Format String b0rken!");
  }
  va_end(args);

  // actually log stuff
  // TODO: Add timestamp
  writeToStdOut(mode, m_buffer);
  m_file << m_buffer;
}

void cut::logging::DefaultManager::
  writeToStdOut( Mode mode, const char* formattedString )
{
  if (formattedString == nullptr)
  {
    return;
  }

#if defined(_WIN32)
  HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

  CONSOLE_SCREEN_BUFFER_INFO initialConsoleState;
  GetConsoleScreenBufferInfo( hStdOut, &initialConsoleState );

  switch (mode)
  {
  case Mode::Normal:
    SetConsoleTextAttribute( hStdOut, 0x07 ); // Regular
    break;
  case Mode::Failure:
    SetConsoleTextAttribute( hStdOut, 0x0C ); // Red
    break;
  case Mode::Success:
    SetConsoleTextAttribute( hStdOut, 0x0A ); // Green
    break;
  default:
    break;
  }
#endif

  printf(formattedString);

#if defined(_WIN32)
  // Restore the default.
  SetConsoleTextAttribute(hStdOut, initialConsoleState.wAttributes);
#endif
}
