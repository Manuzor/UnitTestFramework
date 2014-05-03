#pragma once
#include "string-ref.h"

namespace cut
{
	class IAssertHandler
	{
	public:
		inline static IAssertHandler& instance() { return *s_instance; }

		virtual ~IAssertHandler() = 0;

		virtual void handleFailure(const char* file, size_t line, StringRef message) = 0;
		virtual void handleSuccess(const char* file, size_t line, StringRef message) = 0;

	protected:
		static IAssertHandler* s_instance;
	};
	
	class DefaultAssertHandler : public IAssertHandler
	{
	public:
		DefaultAssertHandler();
		virtual ~DefaultAssertHandler();

		virtual void handleFailure(const char* file, size_t line, StringRef message) override;

		virtual void handleSuccess(const char* file, size_t line, StringRef message) override;
	};


}
