#include "stdafx.h"
#include <windows.h>
#include <cstdarg>

#include "cut/logging/log-manager.h"
#include "cut-detail/log-manager.h"
#include "cut/string-format.h"

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
	m_file()
{
}

cut::DefaultLogManager::~DefaultLogManager()
{
	m_file.close();
}

void
cut::DefaultLogManager::logMessage(LogMode mode, StringRef formattedMessage)
{
	// TODO: Add timestamp
	writeToStdOut(mode, formattedMessage);
	writeToFile(mode, formattedMessage);
}

#ifdef _WIN32

void
cut::DefaultLogManager::writeToStdOut(LogMode mode, StringRef formattedString)
{
	if(!formattedString.valid()) { return; }

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

	printf(formattedString.cString());

	// Restore the default.
	SetConsoleTextAttribute(hStdOut, initialConsoleState.wAttributes);
}

#else

void
cut::DefaultLogManager::writeToStdOut(LogMode mode, StringRef formattedString)
{
	if(!formattedString.valid()) { return; }

	printf(formattedString.cString());
}

#endif // _WIN32

void cut::DefaultLogManager::writeToFile(LogMode mode, StringRef formattedMessage)
{
	if(!m_file.is_open())
	{
		m_file.open(m_fileName);
	}
	m_file << formattedMessage.cString();
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
