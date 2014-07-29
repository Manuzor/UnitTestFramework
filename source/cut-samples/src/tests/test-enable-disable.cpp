#include "stdafx.h"
#include "cut/logging/log-manager.h"

using namespace cut;

UnitTestGroup g_group_1("Enable/Disable Groups and Tests");

UnitTest g_test_1(g_group_1, "Enabled1", []
{
	CUT_ASSERT.succeed("I succeed because I was enabled.");
});

UnitTest g_test_2(g_group_1, "Disabled1", []
{
	CUT_ASSERT.fail("You should never see this message...");
});

UnitTest g_test_3(g_group_1, "Enabled2", []
{
	CUT_ASSERT.succeed("I succeed because I was enabled.");
});

UnitTest g_test_4(g_group_1, "Disabled2", []
{
	CUT_ASSERT.fail("You should never see this message...");
});

//////////////////////////////////////////////////////////////////////////

UnitTestGroup g_group_2("Disabled Group");

UnitTest g_test_disabled_1(g_group_2, "Disabled1", []
{
	CUT_ASSERT.fail("You should never see this message...");
});

UnitTest g_test_disabled_2(g_group_2, "Disabled2", []
{
	CUT_ASSERT.fail("You should never see this message....");
});

UnitTest g_test_disabled_3(g_group_2, "Disabled3", []
{
	CUT_ASSERT.fail("You should never see this message.....");
});
