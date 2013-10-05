#pragma once
#include "cppunit/Common.h"

namespace cppunit
{
  struct Assert
  {
    static void True(bool expr, const char* message = nullptr, ...);
    static void False(bool expr, const char* message = nullptr, ...);

    template<typename T>
    static void Throws(_Lambda& lambda, const char* message = nullptr);

    static void DoesNotThrow(_Lambda& lambda, const char* message = nullptr);

    static void Fail(const char* message = nullptr, ...);
    static void Succeed(const char* message = nullptr, ...);

  private:
    // Non-Copyable
    Assert(){}
    Assert(const Assert&){}
    Assert(Assert&&){}
    const Assert& operator=(const Assert&){}
  };
}

#include "cppunit/Assert.inl"