#pragma once

#include "TokenType.h"
#include "Token.h"

#include "CommonDefs.h"

#include <EASTL/string.h>
#include <EASTL/list.h>
#include <EASTL/hash_map.h>

#include "Logging.h"


NAMESPACE_BEGIN(SkeletonReflect)

class Scanner
{
	static LOG_DECL(logger);

	typedef eastl_size_t Cursor;

	/**
	 * \brief Reserved keywords
	 */
	static eastl::hash_map<eastl::string, TokenType> keywords;

public:

	Scanner(const eastl::string& source);

	void SetSource(const eastl::string& source)
	{
		_source = source;

		// Reset cursors
		_cursor_start = 0;
		_cursor_current = 0;
		_line = 1;
	}

	void ScanTokens();

private:

	void ScanToken();

	void ScanString();
	void ScanNumber();
	void ScanIdentifier();

	bool IsAtEnd()
	{
		return _cursor_current >= _source.size();
	}

	bool IsDigit(char c)
	{
		return c >= '0' && c <= '9';
	}

	bool IsAlpha(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
	}

	bool IsAlphaNumeric(char c)
	{
		return IsAlpha(c) || IsDigit(c);
	}

	// Consume next character
	char Advance()
	{
		return _source.at(_cursor_current++);
	}

	// Try match a character, then consume cursor
	bool Match(char expected)
	{
		if(IsAtEnd())
			return false;
		if(_source.at(_cursor_current) != expected)
			return false;

		_cursor_current++;
		return true;
	}

	// Check the character the cursor is under, don't consume or advance forward though
	char Peek()
	{
		if(IsAtEnd())
			return '\0';
		return _source.at(_cursor_current);
	}

	char PeekNext(Cursor count = 1)
	{
		if(_cursor_current + count >= _source.size())
			return '\0';
		return _source.at(_cursor_current + count);
	}

	void AddToken(TokenType type)
	{
		AddToken(type, "");
	}

	void AddToken(TokenType type, const eastl::string& literal)
	{
		eastl::string text = _source.substr(_cursor_start, _cursor_current - _cursor_start);
		_tokens.push_back({type, text, literal, _line});
	}

	template<typename... Args>
	void Fatal(Args &&... args)
	{
		logger->error(std::forward<Args>(args)...);
	}

private:

	eastl::string _source{};
	eastl::list<Token> _tokens{};

	/**
	 * \brief Custom keywords from a script engine
	 */
	eastl::hash_map<eastl::string, int> _customKeywords{};

	// Cursor trackers
	Cursor _cursor_start = 0;
	Cursor _cursor_current = 0;
	int _line = 1;
};

NAMESPACE_END