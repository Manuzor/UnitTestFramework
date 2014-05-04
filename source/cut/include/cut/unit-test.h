#pragma once
#include "string-ref.h"

namespace cut
{
	class IUnitTestGroup;

	class IUnitTest
	{
	public:
		virtual ~IUnitTest() {}
		virtual void run() = 0;

		virtual StringRef getName() const = 0;
	};

	/// \brief Standard unit test class
	///
	/// Example:
	///	UnitTestGroup g_group1("Unit test group number 1");
	///	UnitTest test1(g_group1, "Unit test number 1 within group number 1", []()
	///	{
	///		CUT_ASSERT.succeed("First test always succeeds!");
	///	});
	///
	class UnitTest : public IUnitTest
	{
	public:
		UnitTest(IUnitTestGroup& testGroup, StringRef testName, Lambda_t lambda);

		virtual void run() override { m_lambda(); }

		virtual StringRef getName() const CUT_OVERRIDE { return m_name; }

	private:
		std::string m_name;
		std::function<void()> m_lambda;
	};
}
