#include "stdafx.h"
#include <windows.h>
#include <cstdarg>
#include <sstream>

#include "cut/logging/log-manager.h"
#include "cut-detail/log-manager.h"
#include "cut/string-format.h"
#include "cut/logging/log-block.h"

cut::ILogManager* cut::ILogManager::s_pInstance = nullptr;

cut::ILogManager&
cut::ILogManager::instance()
{
	static DefaultLogManager default;

	if (s_pInstance == nullptr)
	{
		s_pInstance = &default;
	}

	return *s_pInstance;
}

//////////////////////////////////////////////////////////////////////////

cut::DefaultLogManager::DefaultLogManager() :
	m_fileName("unit-tests.log"),
	m_file(),
	m_blockLevel(0),
	m_blockIndentation(2)
{
}

cut::DefaultLogManager::~DefaultLogManager()
{
	m_file.close();
}

void
cut::DefaultLogManager::logMessage(LogMode mode, StringRef formattedMessage)
{
	std::ostringstream messageStream;

	for(std::size_t i = 0; i < m_blockLevel * m_blockIndentation; ++i)
	{
		messageStream << ' ';
	}

	messageStream << formattedMessage.cString() << '\n';

	// TODO: Add timestamp
	writeToStdOut(mode, messageStream);
	writeToFile(mode, messageStream);
}

#ifdef _WIN32

void
cut::DefaultLogManager::writeToStdOut(LogMode mode, std::ostringstream& formattedString)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO initialConsoleState;
	GetConsoleScreenBufferInfo(hStdOut, &initialConsoleState);

	switch(mode)
	{
	case LogMode::Normal:
		SetConsoleTextAttribute(hStdOut, 0x07); // Regular
		break;
	case LogMode::Failure:
		SetConsoleTextAttribute(hStdOut, 0x0C); // Red
		break;
	case LogMode::Success:
		SetConsoleTextAttribute(hStdOut, 0x0A); // Green
		break;
	default:
		debugBreak();
		break;
	}

	printf(formattedString.str().c_str());

	// Restore the default.
	SetConsoleTextAttribute(hStdOut, initialConsoleState.wAttributes);
}

#else

void
cut::DefaultLogManager::writeToStdOut(LogMode mode, std::ostringstream& formattedString)
{
	printf(formattedString.str().c_str());
}

#endif // _WIN32

void cut::DefaultLogManager::writeToFile(LogMode mode, std::ostringstream& formattedMessage)
{
	if(!m_file.is_open())
	{
		m_file.open(m_fileName);
	}
	m_file << formattedMessage.str();
}

void cut::DefaultLogManager::setLogFileName(StringRef fileName)
{
	if(fileName == m_fileName) { return; }

	if(m_file.is_open())
	{
		m_file.close();
	}

	m_fileName = fileName;
}

const cut::StringRef cut::DefaultLogManager::getLogFileName() const
{
	return m_fileName;
}

void cut::DefaultLogManager::blockBegin()
{
	++m_blockLevel;
}

void cut::DefaultLogManager::blockEnd()
{
	--m_blockLevel;
}

size_t cut::DefaultLogManager::getBlockIndentation() const
{
	return m_blockIndentation;
}

void cut::DefaultLogManager::setBlockIndentation(std::size_t value)
{
	m_blockIndentation = value;
}
