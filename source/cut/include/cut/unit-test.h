#pragma once

namespace cut
{
  class IUnitTest
  {
  public:
    virtual ~IUnitTest() = 0 {}
    virtual void run() = 0;
  };
}