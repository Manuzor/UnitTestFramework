#include "cut/exceptions/unit-test-success.h"

cut::exceptions::UnitTestSuccess::
	UnitTestSuccess() :
	Base(nullptr, 0U, nullptr)
{

}

cut::exceptions::UnitTestSuccess::
	UnitTestSuccess(const char* file, unsigned int line, const char* message) :
	Base(file, line, message)
{
}
