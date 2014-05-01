#pragma once
#include "cut/exceptions/base.h"

namespace cut
{
  namespace exceptions
  {
    class UnitTestSuccess :
      public cut::exceptions::Base
    {
    public:
      UnitTestSuccess();

      UnitTestSuccess(const char* file, unsigned int line, const char* message);

    protected:
    private:
    };

  }
}
