#include "cppunit/exceptions/UnitTestFailure.h"

cppunit::exceptions::UnitTestFailure::
  UnitTestFailure(const char* file, unsigned int line, const char* message) :
  Base(file, line, message)
{

}

cppunit::exceptions::UnitTestFailure::
  ~UnitTestFailure()
{

}


