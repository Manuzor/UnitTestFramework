#pragma once

namespace cut
{
	class IUnitTestGroup;

	class IUnitTest
	{
	public:
		virtual ~IUnitTest() {}
		virtual void run() = 0;

		virtual const char* getName() const = 0;
	};

	class UnitTest : public IUnitTest
	{
	public:
		typedef std::function<void()> Lambda_t;

		UnitTest(IUnitTestGroup& testGroup, const char* testName, Lambda_t lambda);

		virtual void run() override { m_lambda(); }

		virtual const char* getName() const CUT_OVERRIDE{ return m_name; }

	private:
		const char* m_name;
		std::function<void()> m_lambda;
	};
}
