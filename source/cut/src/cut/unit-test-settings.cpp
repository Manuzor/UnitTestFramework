#include "stdafx.h"
#include "cut/testing/unit-test-settings.h"

cut::UnitTestSettings&
cut::settings()
{
	static UnitTestSettings instance;
	return instance;
}
