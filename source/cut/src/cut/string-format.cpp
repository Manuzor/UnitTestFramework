#include "stdafx.h"
#include "cut/string-format.h"
#include "cut/testing/assert.h"

std::string cut::format(CUT_PRINTF_FORMAT_STRING StringRef fmt, ...)
{
	static const std::size_t maxAllocationSize(1024 * 1024 * 10); // 10 MB
	static const std::size_t bufferSize(1024);

	char buffer[bufferSize];
	std::va_list argptr;
	va_start(argptr, fmt);
	CUT_SCOPE_EXIT{ va_end(argptr); };

	int result = vsnprintf_s(buffer,
							 bufferSize - 1, // max characters to write without trailing zero '\0'
							 fmt,
							 argptr);

	if(result < 0)
	{
		for(std::size_t allocationSize = 2 * bufferSize;
			allocationSize < maxAllocationSize;
			allocationSize *= 2)
		{
			char* largeBuffer = new char[allocationSize];
			CUT_SCOPE_EXIT{ delete[] largeBuffer; };

			result = vsnprintf_s(largeBuffer,
								 allocationSize, // size of largeBuffer
								 allocationSize - 1, // max characters to write without trailing zero '\0'
								 fmt,
								 argptr);
			if(result >= 0)
			{
				return std::string(largeBuffer);
			}
		}
		CUT_ASSERT.fail(format("The string you want to format is too large! "
							   "It did not even fit into %u characters.",
							   maxAllocationSize));
	}

	return std::string(buffer);
}
