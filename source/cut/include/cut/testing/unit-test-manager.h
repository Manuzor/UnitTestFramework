#pragma once
#include "cut/testing/unit-test-statistics.h"

namespace cut
{
	class IUnitTestGroup;

	class IUnitTestManager
	{
	public:
		CUT_API static IUnitTestManager& instance();

		virtual ~IUnitTestManager() = 0 {}

		virtual void registerUnitTestGroup(IUnitTestGroup* testGroup) = 0;

		virtual void runAll() = 0;

		virtual void updateStatistics() = 0;
		virtual const UnitTestStatistics& statistics() const = 0;

	protected:
		static IUnitTestManager* s_pInstance;
	};
}
