#pragma once
#include "cut/logging/log-manager.h"
#include "cut/logging/mode.h"

namespace cut
{
	class DefaultLogManager : public ILogManager
	{
	public:
		DefaultLogManager();
		virtual ~DefaultLogManager();

		virtual void logMessage(LogMode mode, StringRef formattedMessage) CUT_OVERRIDE;

		virtual void registerLoggerFunction(LoggerFunction_t func) CUT_OVERRIDE;

		virtual std::size_t getBlockIndentation() const CUT_OVERRIDE;
		virtual void setBlockIndentation(std::size_t value) CUT_OVERRIDE;

	protected:
		virtual void blockBegin() CUT_OVERRIDE;
		virtual void blockEnd() CUT_OVERRIDE;

	private:

		std::size_t m_blockLevel;
		std::size_t m_blockIndentation;
		std::vector<LoggerFunction_t> m_loggers;
	};
}
