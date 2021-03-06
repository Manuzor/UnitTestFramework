#include "stdafx.h"
#include "cut/exceptions.h"
#include "cut/empty-string.h"

cut::exceptions::ExpectionBase::ExpectionBase(const char*  file,
											  std::size_t line,
											  StringRef    message) :
	m_file(file ? file : ""),
	m_line(line),
	m_message(message ? message : "")
{
}

cut::exceptions::ExpectionBase::~ExpectionBase()
{
}

//////////////////////////////////////////////////////////////////////////

cut::exceptions::UnitTestFailure::UnitTestFailure(const char*  file,
												  std::size_t line,
												  StringRef    message) :
	ExpectionBase(file, line, message)
{

}

cut::exceptions::UnitTestFailure::~UnitTestFailure()
{

}

//////////////////////////////////////////////////////////////////////////

cut::exceptions::UnitTestSuccess::UnitTestSuccess() :
	ExpectionBase(nullptr, 0, emptyString())
{

}

cut::exceptions::UnitTestSuccess::UnitTestSuccess(const char* file,
												  std::size_t line,
												  StringRef message) :
	ExpectionBase(file, line, message)
{

}

cut::exceptions::UnitTestSuccess::~UnitTestSuccess()
{

}

//////////////////////////////////////////////////////////////////////////

cut::exceptions::UnitTestNotImplemented::UnitTestNotImplemented() :
	ExpectionBase(nullptr, 0, emptyString())
{
}

cut::exceptions::UnitTestNotImplemented::UnitTestNotImplemented(const char* file,
																std::size_t line,
																StringRef message) :
	ExpectionBase(file, line, message)
{
}

cut::exceptions::UnitTestNotImplemented::~UnitTestNotImplemented()
{

}
