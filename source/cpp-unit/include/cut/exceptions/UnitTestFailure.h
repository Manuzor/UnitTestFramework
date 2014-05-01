#pragma once
#include "cppunit/exceptions/Base.h"

namespace cppunit
{
  namespace exceptions
  {
    class UnitTestFailure :
      public cppunit::exceptions::Base
    {
    public:
      UnitTestFailure(const char* file, unsigned int line, const char* message);

      virtual ~UnitTestFailure();

    protected:
    private:
    };
  }
}