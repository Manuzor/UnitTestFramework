
#include "cut/common.h"
#include "cut/assert.h"
#include "cut/unit-test.h"
#include "cut/unit-test-group.h"
#include "cut/unit-test-manager.h"
#include "cut/unit-test-statistics.h"

#define CUT_TEST(groupRef, className) class CUT_CONCAT(UnitTest_, groupRef, _, className) :    \
	public ::cut::UnitTestBase                                                                 \
{                                                                                              \
public:                                                                                        \
	CUT_CONCAT(UnitTest_, groupRef, _, className)()                                            \
	{                                                                                          \
		groupRef.registerUnitTest(CUT_TOSTRING(className), this);                              \
	}                                                                                          \
	virtual void run() CUT_OVERRIDE;                                                           \
};                                                                                             \
CUT_CONCAT(UnitTest_, groupRef, _, className) CUT_CONCAT(g_unitTest_, groupRef, _, className); \
void CUT_CONCAT(UnitTest_, groupRef, _, className)::run()
