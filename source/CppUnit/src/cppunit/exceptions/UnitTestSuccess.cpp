#include "cppunit/exceptions/UnitTestSuccess.h"

cppunit::exceptions::UnitTestSuccess::
  UnitTestSuccess() :
  Base(nullptr, 0U, nullptr)
{

}

cppunit::exceptions::UnitTestSuccess::
  UnitTestSuccess(const char* file, unsigned int line, const char* message) :
  Base(file, line, message)
{
}
