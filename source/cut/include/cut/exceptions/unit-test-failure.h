#pragma once
#include "cut/exceptions/base.h"

namespace cut
{
  namespace exceptions
  {
    class UnitTestFailure :
      public cut::exceptions::Base
    {
    public:
      UnitTestFailure(const char* file, unsigned int line, const char* message);

      virtual ~UnitTestFailure();

    protected:
    private:
    };
  }
}
