#include "cut/logging/log-manager.h"

CUT_FORCE_INLINE
cut::loggers::StdOutWriter::StdOutWriter(ILogManager& logManager)
{
	using namespace std::placeholders;
	logManager.registerLoggerFunction(std::bind(&StdOutWriter::logMessageHandler, this, _1));
}

#ifdef _WIN32

CUT_FORCE_INLINE
void
cut::loggers::StdOutWriter::logMessageHandler(const LoggerInfo& loggerInfo)
{
	{
		const auto totalIndentationWidth = loggerInfo.indentationLevel * loggerInfo.indentationWidthPerLevel;
		for(std::size_t i = 0; i < totalIndentationWidth; ++i)
		{
			printf(" ");
		}
	}

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO initialConsoleState;
	GetConsoleScreenBufferInfo(hStdOut, &initialConsoleState);

	switch(loggerInfo.logMode)
	{
	case LogMode::Normal:
		SetConsoleTextAttribute(hStdOut, 0x07); // Regular
		break;
	case LogMode::Warning:
		SetConsoleTextAttribute(hStdOut, 0x0E); // Yellow
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

	printf("%s\n", loggerInfo.message.cString());

	// Restore the default.
	SetConsoleTextAttribute(hStdOut, initialConsoleState.wAttributes);
}

#else

CUT_FORCE_INLINE
void
cut::loggers::StdOutWriter::logMessageHandler(const LoggerInfo& loggerInfo)
{
	{
		const auto totalIndentationWidth = loggerInfo.indentationLevel * loggerInfo.indentationWidthPerLevel;
		for(std::size_t i = 0; i < totalIndentationWidth; ++i)
		{
			printf(" ");
		}
	}

	printf("%s \n", loggerInfo.message.cString());
}

#endif // _WIN32

//////////////////////////////////////////////////////////////////////////

CUT_FORCE_INLINE
cut::loggers::FileWriter::FileWriter(ILogManager& logManager, StringRef fileName) :
	m_file(fileName.cString())
{
	using namespace std::placeholders;
	logManager.registerLoggerFunction(std::bind(&FileWriter::logMessageHandler, this, _1));
}

CUT_FORCE_INLINE
cut::loggers::FileWriter::~FileWriter()
{
	m_file.close();
}

CUT_FORCE_INLINE
void
cut::loggers::FileWriter::logMessageHandler(const LoggerInfo& loggerInfo)
{
	{
		const auto totalIndentationWidth = loggerInfo.indentationLevel * loggerInfo.indentationWidthPerLevel;
		for(std::size_t i = 0; i < totalIndentationWidth; ++i)
		{
		m_file << ' ';
		}
	}

	m_file << loggerInfo.message.cString()
		   << '\n';
}

//////////////////////////////////////////////////////////////////////////

CUT_FORCE_INLINE
cut::loggers::VisualStudioWriter::VisualStudioWriter(ILogManager& logManager)
{
	using namespace std::placeholders;
	logManager.registerLoggerFunction(std::bind(&VisualStudioWriter::logMessageHandler, this, _1));
}

#ifdef _WIN32

CUT_FORCE_INLINE
void
cut::loggers::VisualStudioWriter::logMessageHandler(const LoggerInfo& loggerInfo)
{
	{
		const auto totalIndentationWidth = loggerInfo.indentationLevel * loggerInfo.indentationWidthPerLevel;
		for(std::size_t i = 0; i < totalIndentationWidth; ++i)
		{
			OutputDebugStringA(" ");
		}
	}

	OutputDebugStringA(loggerInfo.message.cString());
	OutputDebugStringA("\n");
}

#else

CUT_FORCE_INLINE
void
cut::loggers::VisualStudioWriter::logMessageHandler(const LoggerInfo& loggerInfo)
{
}

#endif
