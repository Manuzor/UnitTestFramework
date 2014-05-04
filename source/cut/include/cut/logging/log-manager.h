#pragma once

#include "cut/streams/output-file.h"
#include "cut/logging/mode.h"

#ifndef CUT_LOG_FORMATBUFFERSIZE
#define CUT_LOG_FORMATBUFFERSIZE 1024
#endif // CUT_LOG_FORMATBUFFERSIZE

namespace cut
{
	class ILogManager
	{
	public:
		virtual ~ILogManager() = 0 {}

		virtual void logMessage(LogMode mode, const char* formatString, ...) = 0;
	};

	class DefaultLogManager :
		public ILogManager
	{
	public:

		static DefaultLogManager& instance();

		DefaultLogManager();

		virtual ~DefaultLogManager();

		virtual void logMessage(LogMode mode, const char* formatString, ...);

	private:
		void writeToStdOut(LogMode mode, const char* formattedString);

		streams::OutputFile m_file;
		char* m_buffer;
	};
}
