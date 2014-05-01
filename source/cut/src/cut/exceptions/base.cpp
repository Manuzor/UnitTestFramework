#include "cppunit/exceptions/Base.h"

cppunit::exceptions::Base::
  Base( const char* file, unsigned int line, const char* message ) :
  m_file(file ? file : ""),
  m_line(line),
  m_message(message)
{
}

cppunit::exceptions::Base::
  ~Base()
{
}
