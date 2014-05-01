#include "cut/exceptions/base.h"

cut::exceptions::Base::
	Base( const char* file, unsigned int line, const char* message ) :
	m_file(file ? file : ""),
	m_line(line),
	m_message(message)
{
}

cut::exceptions::Base::
	~Base()
{
}
