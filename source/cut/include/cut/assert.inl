#include "cut/exceptions/unit-test-success.h"
#include "cut/exceptions/unit-test-failure.h"

template<typename T_Exception>
void
cut::assert::throws(_Lambda& lambda, const char* message)
{
	try
	{
		lambda();
		throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
	}
	catch (T_Exception&)
	{
		// Success!
		return;
	}
	catch (...)
	{
		throw exceptions::UnitTestFailure(__FILE__, __LINE__, message);
	}
}

