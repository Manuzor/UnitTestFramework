#include "stdafx.h"

using namespace cut;

namespace
{
	UnitTestGroup g_group("exceptions");

	UnitTest g_test1(g_group, "throws", [](){
		CUT_ASSERT.throws<std::exception>([](){
			throw std::exception("test throw");
		}, "std::exception should be caught!");

		CUT_ASSERT.throws<int>([](){
			throw 123;
		}, "If ANYTHING is thrown, it should also be caught!");
	});

	UnitTest g_test2(g_group, "throwsNothing", [](){
		CUT_ASSERT.throwsNothing([](){
			throw 123;
		}, "The unit test framework catches all kind of things...");
	});
}
