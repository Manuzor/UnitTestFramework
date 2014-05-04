#pragma once
#include "cut/unit-test-manager.h"

namespace cut
{
	class DefaultUnitTestManager : public IUnitTestManager
	{
	public:

		DefaultUnitTestManager();
		virtual ~DefaultUnitTestManager();

		virtual void registerUnitTestGroup(const char* groupName, IUnitTestGroup* testGroup);

		virtual void runAll();

		virtual std::size_t numberOfUnitTestGroups();

	protected:
	private:
		UnitTestStatistics m_statistics;
		UnitTestGroupMap m_unitTestGroups;
	};
}
