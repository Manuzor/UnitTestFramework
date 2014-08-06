#include "stdafx.h"

using namespace cut;

UnitTestGroup g_group_Group1("Group 1");

UnitTest g_test1(g_group_Group1, "Succeed", [](){
	CUT_ASSERT.isTrue(true);
	CUT_ASSERT.isFalse(false);
	CUT_ASSERT.succeed();
});

UnitTest g_test2(g_group_Group1, "Succeed with message", [](){
	CUT_ASSERT.succeed("Hello World.");
});

UnitTest g_test3(g_group_Group1, "Succeed with formatted message", [](){
	CUT_ASSERT.succeed(format("Hello %s", "World"));
});

UnitTest g_test4(g_group_Group1, "Fail", [](){
	CUT_ASSERT.fail();
});

UnitTest g_test5(g_group_Group1, "NotImplemented", [](){
	CUT_ASSERT.notImplemented("This is the message of a test that is not implemented.");
});

UnitTest g_test6(g_group_Group1, "NotImplementedWithoutMessage", [](){
	CUT_ASSERT.notImplemented();
});
