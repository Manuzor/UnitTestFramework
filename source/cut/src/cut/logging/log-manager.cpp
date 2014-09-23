#include "stdafx.h"
#include <windows.h>
#include <cstdarg>
#include <sstream>

#include "cut/logging/log-manager.h"
#include "cut-detail/log-manager.h"
#include "cut/string-format.h"
#include "cut/logging/log-block.h"

cut::ILogManager*
cut::ILogManager::s_pInstance = nullptr;

cut::ILogManager&
cut::ILogManager::instance()
{
	if (s_pInstance == nullptr)
	{
		static DefaultLogManager default; // Will only be created if the user did not specify an instance.
		s_pInstance = &default;
	}

	return *s_pInstance;
}

//////////////////////////////////////////////////////////////////////////

cut::DefaultLogManager::DefaultLogManager() :
	m_blockLevel(0),
	m_blockIndentation(2),
	m_loggers()
{
	m_loggers.reserve(4);
}

cut::DefaultLogManager::~DefaultLogManager()
{
	m_loggers.clear();
}

void
cut::DefaultLogManager::logMessage(LogMode mode, StringRef formattedMessage)
{
	// TODO: Add timestamp?

	LoggerInfo info;

	info.logMode = mode;
	info.message = formattedMessage;
	info.indentationLevel = m_blockLevel;
	info.indentationWidthPerLevel = m_blockIndentation;

	for (auto& logger : m_loggers)
	{
		if (logger)
		{
			logger(info);
		}
	}
}

void
cut::DefaultLogManager::addLoggerFunction(LoggerFunction_t func)
{
	m_loggers.push_back(func);
}

void
cut::DefaultLogManager::addBlockListener(BlockListenerFunction_t func)
{
	m_blockListeners.push_back(func);
}

void
cut::DefaultLogManager::blockBegin(StringRef blockName)
{
	if (!m_blockListeners.empty())
	{
		LogBlockInfo info
		{
			LogBlockAction::Begin,
			m_blockLevel,
			m_blockIndentation,
			blockName
		};

		for (auto& listener : m_blockListeners)
		{
			if (listener)
			{
				listener(info);
			}
		}
	}

	++m_blockLevel;
}

void
cut::DefaultLogManager::blockEnd(StringRef blockName)
{
	--m_blockLevel;

	if (!m_blockListeners.empty())
	{
		LogBlockInfo info
		{
			LogBlockAction::End,
			m_blockLevel,
			m_blockIndentation,
			blockName
		};

		for (auto& listener : m_blockListeners)
		{
			if (listener)
			{
				listener(info);
			}
		}
	}
}

size_t
cut::DefaultLogManager::getBlockIndentation() const
{
	return m_blockIndentation;
}

void
cut::DefaultLogManager::setBlockIndentation(std::size_t value)
{
	m_blockIndentation = value;
}
