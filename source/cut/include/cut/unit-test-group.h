#pragma once
#include "cut/string-ref.h"

namespace cut
{
	class IUnitTest;

	typedef std::vector<IUnitTest*> UnitTestContainer;

	class IUnitTestGroup
	{
	public:
		virtual ~IUnitTestGroup() = 0 {}

		virtual void registerUnitTest(IUnitTest* unitTest) = 0;

		virtual std::size_t runAllTests() = 0;

		virtual std::size_t numberOfUnitTests() = 0;

		virtual StringRef getName() const = 0;
	};

	class UnitTestGroup :
		public IUnitTestGroup
	{
	public:

		UnitTestGroup(StringRef groupName);
		virtual ~UnitTestGroup();

		virtual void registerUnitTest(IUnitTest* unitTest) CUT_OVERRIDE;

		virtual unsigned int runAllTests() CUT_OVERRIDE;

		virtual std::size_t numberOfUnitTests();

		virtual StringRef getName() const CUT_OVERRIDE;


	protected:
		std::string m_name;
		std::size_t m_numFailedTests;
		UnitTestContainer m_unitTests;
	};
}
