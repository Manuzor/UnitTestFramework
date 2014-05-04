#include "stdafx.h"

using namespace cut;

UnitTestGroup g_group_Group1("Group 1");

UnitTest g_test1(g_group_Group1, "Hello World", [](){
	CUT_ASSERT.isTrue(true);
	CUT_ASSERT.isFalse(false);
	CUT_ASSERT.succeed();
});
