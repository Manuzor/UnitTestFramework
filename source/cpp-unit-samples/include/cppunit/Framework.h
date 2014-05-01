#pragma once

#if !defined(_WIN32) && !defined(_WIN64)
#error "Current compiler is not supported!"
#endif

#include "cppunit/Common.h"
#include "cppunit/UnitTestManager.h"
#include "cppunit/UnitTestGroup.h"
#include "cppunit/UnitTest.h"
#include "cppunit/Assert.h"


#define CPPUNIT_GROUP(groupName) class UnitTestGroup_##groupName :                \
  public ::cppunit::UnitTestGroup                                                 \
{                                                                                 \
public:                                                                           \
  UnitTestGroup_##groupName() :                                                   \
    ::cppunit::UnitTestGroup(#groupName){}                                        \
};                                                                                \
UnitTestGroup_##groupName g_unitTestGroup_##groupName

#define CPPUNIT_TEST(groupName, className) class UnitTest_##groupName##_##className :  \
  public ::cppunit::IUnitTest                                                          \
{                                                                                      \
public:                                                                                \
  UnitTest_##groupName##_##className()                                                 \
  {                                                                                    \
    g_unitTestGroup_##groupName.registerUnitTest(#className, this);                    \
  }                                                                                    \
  virtual void run() override;                                                         \
};                                                                                     \
UnitTest_##groupName##_##className g_unitTest_##groupName##_##className;               \
void UnitTest_##groupName##_##className::run()
