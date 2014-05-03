#pragma once
#include "cut/unit-test-statistics.h"

namespace cut
{
	class IUnitTestGroup;

	typedef std::map<const char*, IUnitTestGroup*> UnitTestGroupMap;

	class IUnitTestManager
	{
	public:
		virtual ~IUnitTestManager() = 0 {}

		virtual void registerUnitTestGroup(const char* groupName, IUnitTestGroup* testGroup) = 0;

		virtual void runAll() = 0;

		virtual size_t numberOfUnitTestGroups() = 0;
	};

	class DefaultUnitTestManager :
		public IUnitTestManager
	{
	public:
		static DefaultUnitTestManager& instance();

		DefaultUnitTestManager();
		virtual ~DefaultUnitTestManager();

		virtual void registerUnitTestGroup(const char* groupName, IUnitTestGroup* testGroup);

		virtual void runAll();

		virtual size_t numberOfUnitTestGroups();

	protected:
	private:
		UnitTestStatistics m_statistics;
		UnitTestGroupMap m_unitTestGroups;
	};

	typedef CUT_TYPE_TESTMANAGER TestManager;
}
