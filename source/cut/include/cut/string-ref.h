#pragma once

namespace cut
{
	struct StringRef
	{
		enum Enum
		{
			CString,
			StdString,
		};

		inline static const std::string& emptyString()
		{
			static std::string str("");
			return str;
		}

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
			m_both(rhs.m_both),
			m_type(rhs.m_type)
		{
		}

		inline StringRef& operator = (const StringRef& rhs)
		{
			m_both = rhs.m_both;
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
		}

		inline operator bool()
		{
			return m_both != nullptr;
		}

		inline operator const char*()
		{
			if(m_type == CString && m_pCString)
			{
				return m_pCString;
			}

			return nullptr;
		}

		inline operator const std::string&()
		{
			if(m_type == StdString && m_pStdString)
			{
				return *m_pStdString;
			}

			return emptyString();
		}

	private:
		struct
		{
			union
			{
				const char* m_pCString;
				const std::string* m_pStdString;
			};
			void* m_both;
		};

		Enum m_type;
	};
	
}
