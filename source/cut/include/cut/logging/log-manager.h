#pragma once

#include "cut/logging/mode.h"
#include "cut/string-ref.h"

namespace cut
{
	class ILogManager
	{
	public:
		static ILogManager& instance();

		virtual ~ILogManager() = 0 {}

		/// \remark If you need to format your message, use cut::format
		virtual void logMessage(LogMode mode, StringRef formattedMessage) = 0;

		virtual void setLogFileName(StringRef fileName) = 0;
		virtual const StringRef getLogFileName() const = 0;

	protected:
		static ILogManager* s_pInstance;
	};
}
