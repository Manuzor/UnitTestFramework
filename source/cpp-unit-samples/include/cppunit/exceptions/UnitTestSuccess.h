#pragma once
#include "cppunit/exceptions/Base.h"

namespace cppunit
{
  namespace exceptions
  {
    class UnitTestSuccess :
      public cppunit::exceptions::Base
    {
    public:
      UnitTestSuccess();

      UnitTestSuccess(const char* file, unsigned int line, const char* message);

    protected:
    private:
    };

  }
}