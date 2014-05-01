#pragma once

#if !defined(_WIN32) && !defined(_WIN64)
#error "Current compiler is not supported!"
#endif

#include "cut/common.h"
#include "cut/unit-test-manager.h"
#include "cut/unit-test-group.h"
#include "cut/unit-test.h"
#include "cut/assert.h"


#define CUT_GROUP(groupName) class UnitTestGroup_##groupName :                \
  public ::cut::UnitTestGroup                                                 \
{                                                                                 \
public:                                                                           \
  UnitTestGroup_##groupName() :                                                   \
    ::cut::UnitTestGroup(#groupName){}                                        \
};                                                                                \
UnitTestGroup_##groupName g_unitTestGroup_##groupName

#define CUT_TEST(groupName, className) class UnitTest_##groupName##_##className :  \
  public ::cut::IUnitTest                                                          \
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
