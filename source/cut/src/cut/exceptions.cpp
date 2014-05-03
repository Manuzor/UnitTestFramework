#include "stdafx.h"
#include "cut/exceptions.h"

cut::exceptions::ExpectionBase::ExpectionBase(const char* file,
											  unsigned int line,
											  const char* message) :
	m_file(file ? file : ""),
	m_line(line),
	m_message(message ? message : "")
{
}

cut::exceptions::ExpectionBase::
~ExpectionBase()
{
}

cut::exceptions::UnitTestFailure::UnitTestFailure(const char*  file,
												  unsigned int line,
												  const char*  message) :
												  ExpectionBase(file, line, message)
{

}

cut::exceptions::UnitTestFailure::~UnitTestFailure()
{

}

