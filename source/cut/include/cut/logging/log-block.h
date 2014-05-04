#pragma once
#include "cut/string-ref.h"

namespace cut
{
	struct LogBlock
	{
		LogBlock(StringRef name);
		~LogBlock();

	private:
		std::string m_begin;
		std::string m_end;
	};
}
