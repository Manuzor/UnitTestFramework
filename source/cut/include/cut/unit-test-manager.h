#pragma once
#include "cut/unit-test-statistics.h"

namespace cut
{
	class IUnitTestGroup;

	typedef std::map<const char*, IUnitTestGroup*> UnitTestGroupMap;

	class IUnitTestManager
	{
	public:
		static IUnitTestManager& instance();

		virtual ~IUnitTestManager() = 0 {}

		virtual void registerUnitTestGroup(const char* groupName, IUnitTestGroup* testGroup) = 0;

		virtual void runAll() = 0;

		virtual std::size_t numberOfUnitTestGroups() = 0;

	protected:
		static IUnitTestManager* s_instance;
	};
}
