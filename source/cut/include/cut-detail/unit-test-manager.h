#pragma once
#include "cut/testing/unit-test-manager.h"
#include "cut/testing/unit-test-statistics.h"

namespace cut
{
	typedef std::vector<IUnitTestGroup*> UnitTestGroupContainer;

	class DefaultUnitTestManager : public IUnitTestManager
	{
	public:

		DefaultUnitTestManager();
		virtual ~DefaultUnitTestManager();

		virtual void registerUnitTestGroup(IUnitTestGroup* testGroup) CUT_OVERRIDE;

		virtual void runAll() CUT_OVERRIDE;

		virtual void updateStatistics() CUT_OVERRIDE;
		virtual const UnitTestStatistics& statistics() const CUT_OVERRIDE;

	protected:
	private:
		UnitTestStatistics m_statistics;
		UnitTestGroupContainer m_unitTestGroups;
	};
}
