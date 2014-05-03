#pragma once

namespace cut
{
	class IAssertHandler
	{
	public:
		inline static IAssertHandler& instance() { return *s_instance; }

		virtual ~IAssertHandler() = 0;

		virtual void handleFailure(const char* file, size_t line, const char* message) = 0;
		virtual void handleSuccess(const char* file, size_t line, const char* message) = 0;

	protected:
		static IAssertHandler* s_instance;
	};
	
	class DefaultAssertHandler : public IAssertHandler
	{
	public:
		DefaultAssertHandler();
		virtual ~DefaultAssertHandler();

		virtual void handleFailure(const char* file, size_t line, const char* message) override;

		virtual void handleSuccess(const char* file, size_t line, const char* message) override;
	};


}
