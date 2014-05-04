#pragma once
#include "cut/logging/log-manager.h"
#include "cut/streams/output-file.h"
#include "cut/logging/mode.h"

namespace cut
{
	class DefaultLogManager : public ILogManager
	{
	public:
		DefaultLogManager();
		virtual ~DefaultLogManager();

		virtual void logMessage(LogMode mode, StringRef formattedMessage) CUT_OVERRIDE;

		/// \remark This method closes the output file
		virtual void setLogFileName(StringRef fileName) CUT_OVERRIDE;
		virtual const StringRef getLogFileName() const CUT_OVERRIDE;

	private:
		void writeToStdOut(LogMode mode, StringRef formattedString);
		void writeToFile(LogMode mode, StringRef formattedMessage);

		streams::OutputFile m_file;
		std::string m_fileName;
	};
}
