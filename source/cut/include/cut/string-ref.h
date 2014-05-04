#pragma once
#include "cut/empty-string.h"

namespace cut
{
	struct StringRef
	{
		enum Enum
		{
			CString,
			StdString,
		};

	public:

		inline StringRef(const char* szString) :
			m_pCString(szString),
			m_type(CString)
		{
		}

		inline StringRef(const std::string& stdString) :
			m_pStdString(&stdString),
			m_type(StdString)
		{
		}

		inline StringRef(const StringRef& rhs) :
			m_pAll(rhs.m_pAll),
			m_type(rhs.m_type)
		{
		}

		inline StringRef& operator = (const StringRef& rhs)
		{
			m_pAll = rhs.m_pAll;
			m_type = rhs.m_type;
		}

		inline const char* cString()
		{
			switch(m_type)
			{
			case CString:   return m_pCString;
			case StdString: return m_pStdString->c_str();
			}

			CUT_DEBUG_BREAK;
			throw std::exception("Invalid type for StringRef!");
			return nullptr;
		}

		inline bool valid()
		{
			return m_pAll != nullptr;
		}

		inline bool empty()
		{
			if(valid())
			{
				switch(m_type)
				{
				case CString:   return strlen(m_pCString) == 0;
				case StdString: return m_pStdString->empty();
				}
			}
			
			return true;
		}

		inline operator bool()
		{
			return valid();
		}

		inline operator const char*()
		{
			return cString();
		}

	private:
		union
		{
			const char* m_pCString;
			const std::string* m_pStdString;

			void* m_pAll;
		};

		Enum m_type;
	};
	
}
