#pragma once

namespace cppunit
{
  class IUnitTest
  {
  public:
    virtual ~IUnitTest() = 0 {}
    virtual void run() = 0;
  };
}