#pragma once

namespace cut
{
	// Forward declarations
	class IUnitTest;

	// typedefs
	typedef std::map<const char*, IUnitTest*> UnitTestMap;

	// class definitions
	class IUnitTestGroup
	{
	public:
		virtual ~IUnitTestGroup() = 0 {}

		virtual void registerUnitTest(IUnitTest* unitTest) = 0;

		virtual unsigned int runAllTests() = 0;

		virtual std::size_t numberOfUnitTests() = 0;
	};

	class UnitTestGroup :
		public IUnitTestGroup
	{
	public:

		UnitTestGroup(const char* groupName);

	virtual ~UnitTestGroup();

		virtual void registerUnitTest(IUnitTest* unitTest) override;

		virtual unsigned int runAllTests() override;

		virtual std::size_t numberOfUnitTests();

	protected:

		UnitTestMap m_unitTests;

	private:
	};
}
