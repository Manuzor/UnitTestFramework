#pragma once

#include "cut/containers/map.h"

namespace cut
{
	// Forward declarations
	class IUnitTest;

	// typedefs
	typedef containers::Map<const char*, IUnitTest*>::type UnitTestMap;

	// class definitions
	class IUnitTestGroup
	{
	public:
		virtual ~IUnitTestGroup() = 0 {}

		virtual void registerUnitTest(const char* unitTestName, IUnitTest* unitTest) = 0;

		virtual unsigned int runAllTests() = 0;

		virtual size_t numberOfUnitTests() = 0;
	};

	class UnitTestGroup :
		public IUnitTestGroup
	{
	public:

		UnitTestGroup(const char* groupName);

	virtual ~UnitTestGroup();

		virtual void registerUnitTest(const char* unitTestName, IUnitTest* unitTest) override;

		virtual unsigned int runAllTests() override;

		virtual size_t numberOfUnitTests();

	protected:

		UnitTestMap m_unitTests;

	private:
	};
}
