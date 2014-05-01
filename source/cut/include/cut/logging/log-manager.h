#pragma once

#include "cut/streams/output-file.h"
#include "cut/logging/mode.h"

#ifndef CUT_LOG_FORMATBUFFERSIZE
#define CUT_LOG_FORMATBUFFERSIZE 1024
#endif // !CUT_LOG_FORMATBUFFERSIZE

namespace cut
{
	namespace logging
	{
		class IManager
		{
		public:
			virtual ~IManager() = 0 {}

			virtual void logMessage(Mode mode, const char* formatString, ...) = 0;
		};

		class DefaultManager :
			public IManager
		{
		public:

			static DefaultManager* instance();

			DefaultManager();

			virtual ~DefaultManager();

			virtual void logMessage(Mode mode, const char* formatString, ...);

		private:
			void writeToStdOut(Mode mode, const char* formattedString);

			streams::OutputFile m_file;
			char* m_buffer;
		};
	}
}
