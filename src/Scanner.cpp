#include "SkeletonReflect/Scanner.h"


std::shared_ptr<spdlog::logger> Scanner::logger = spdlog::stdout_color_mt("Scanner");

eastl::hash_map<eastl::string, TokenType> Scanner::keywords = {
	{ "class", CLASS },
	{ "const", CONST },
	{ "static", STATIC },

	{ "public", PUBLIC },
	{ "private", PRIVATE },

	{ "void", VOID },
	{ "int", INT },
	{ "bool", BOOL },

	{ "SKCLASS", MACRO_CLASS_DECL },
	{ "SK_GENERATED_BODY", MACRO_GEN_BODY },
	{ "SKPROPERTY", MACRO_FUNC_DECL },
	{ "SKFUNCTION", MACRO_FUNC_DECL}
};

void Scanner::ScanTokens()
{
	while(!IsAtEnd())
	{
		// Set sub scanner cursor beginning to where we have scanned up to
		_cursor_start = _cursor_current;

		// Attempt to scan next token
		ScanToken();
	}

	_tokens.push_back({END_OF_FILE, "", "", _line});
}

void Scanner::ScanToken()
{
	char c = Advance();
	switch(c)
	{
	case '(': AddToken(LEFT_PAREN); break;
	case ')': AddToken(RIGHT_PAREN); break;
	case '{': AddToken(LEFT_BRACE); break;
	case '}': AddToken(RIGHT_BRACE); break;
	case ',': AddToken(COMMA); break;
	case '.': AddToken(DOT); break;
	case '-': AddToken(MINUS); break;
	case '+': AddToken(PLUS); break;
	case ';': AddToken(SEMICOLON); break;
	case ':': AddToken(COLON); break;
	case '*': AddToken(STAR); break;

	case '!': AddToken(Match('=') ? BANG_EQUAL : BANG); break;
	case '=': AddToken(Match('=') ? EQUAL_EQUAL : EQUAL); break;
	case '<': AddToken(Match('=') ? LESS_EQUAL : LESS); break;
	case '>': AddToken(Match('=') ? GREATER_EQUAL : GREATER); break;

	case '#': AddToken(HASH); break;

	case '/':
	{
		// Full line comments
		if(Match('/'))
		{
			while(Peek() != '\n' && !IsAtEnd())
				Advance();
		}
		else
		{
			AddToken(SLASH);
		}
	} break;

	// Ignore whitespace.
	case ' ':
	case '\r':
	case '\t':
		break;

	// Advance line tracker
	case '\n': _line++; break;

	case '"': ScanString(); break;

	default:
	{
		if(IsDigit(c))
		{
			ScanNumber();
		}
		else if(IsAlpha(c))
		{
			ScanIdentifier();
		}
		else
		{
			Fatal("Unexpected character {} on line {}", c, _line);
		}
	} break;
	}
}

void Scanner::ScanString()
{
	while(Peek() != '"' && !IsAtEnd())
	{
		if(Peek() == '\n')
			_line++;
		Advance();
	}

	if(IsAtEnd())
	{
		Fatal("Unterminated string");
		return;
	}

	// The closing "
	Advance();

	eastl::string str = _source.substr(_cursor_start + 1, _cursor_current - 1 - (_cursor_start + 1));
	AddToken(STRING, str);
}

void Scanner::ScanNumber()
{
	while(IsDigit(Peek()))
		Advance();

	// Floating point
	if(Peek() == '.' && IsDigit(PeekNext()))
	{
		Advance();

		while(IsDigit(Peek()))
			Advance();
	}

	AddToken(NUMBER, _source.substr(_cursor_start, _cursor_current - _cursor_start));
}

void Scanner::ScanIdentifier()
{
	while(IsAlphaNumeric(Peek()))
		Advance();

	eastl::string str = _source.substr(_cursor_start, _cursor_current - _cursor_start);
	TokenType type = IDENTIFIER;
	if(keywords.count(str) > 0)
		type = keywords[str];

	AddToken(type);
}