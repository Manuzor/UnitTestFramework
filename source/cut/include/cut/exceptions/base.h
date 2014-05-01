#pragma once
#include <exception>

namespace cut
{
  namespace exceptions
  {
    class Base : 
      public std::exception
    {
    public:
      Base(const char* file, unsigned int line, const char* message);

      virtual ~Base();
      const char* file() const { return m_file; }
      const unsigned int line() const { return m_line; }
      const char* message() const { return m_message; }

    protected:
      const char* m_file;
      unsigned int m_line;
      const char* m_message;
    private:
    };
  }
}