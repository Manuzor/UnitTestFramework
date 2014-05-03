#pragma once
#include <exception>
#include "cut/string-ref.h"

namespace cut
{
	namespace exceptions
	{
		class ExpectionBase : public std::exception
		{
		public:
			ExpectionBase(const char* file, unsigned int line, StringRef message);

			virtual ~ExpectionBase();
			
			const char* file() const { return m_file; }
			const unsigned int line() const { return m_line; }

			const std::string& message() const { return m_message; }
			std::string&       message()       { return m_message; }

		private:
			const char* m_file;
			unsigned int m_line;
			std::string m_message;
		};

		class UnitTestFailure : public ExpectionBase
		{
		public:
			UnitTestFailure(const char* file, unsigned int line, StringRef message);

			virtual ~UnitTestFailure();

		protected:
		private:
		};

		class UnitTestSuccess : public ExpectionBase
		{
		public:
			UnitTestSuccess();

			UnitTestSuccess(const char* file, unsigned int line, StringRef message);

		protected:
		private:
		};
	}
}
