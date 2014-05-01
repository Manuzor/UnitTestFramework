#include "cppunit/exceptions/UnitTestSuccess.h"
#include "cppunit/exceptions/UnitTestFailure.h"

template<typename T_Exception>
void
cppunit::Assert::Throws(_Lambda& lambda, const char* message)
{
	try
	{
		lambda();
		throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
	}
	catch (T_Exception&)
	{
		// Success!
	}
	catch (...)
	{
		throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
	}
}

