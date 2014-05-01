#include "cut/exceptions/unit-test-failure.h"

cut::exceptions::UnitTestFailure::
  UnitTestFailure(const char* file, unsigned int line, const char* message) :
  Base(file, line, message)
{

}

cut::exceptions::UnitTestFailure::
  ~UnitTestFailure()
{

}


