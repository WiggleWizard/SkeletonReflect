#pragma once

#include "TokenType.h"

#include <EASTL/string.h>
#include <EASTL/variant.h>

#include <spdlog/fmt/fmt.h>


class Token
{
public:
	Token(TokenType t, const eastl::string& inLexeme, const eastl::string& inLiteral, int lineNumber)
		: type(t)
		, lexeme(inLexeme)
		, literal(inLiteral)
		, line(lineNumber)
	{}

	TokenType type;
	eastl::string lexeme;
	eastl::string literal;
	int line;
};

template<>
struct fmt::formatter<Token>
{
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx);

	template<typename FormatContext>
	auto format(const Token& token, FormatContext& ctx);
};

template<typename ParseContext>
constexpr auto fmt::formatter<Token>::parse(ParseContext& ctx)
{
	return ctx.begin();
}

template<typename FormatContext>
auto fmt::formatter<Token>::format(const Token& t, FormatContext& ctx)
{
	return fmt::format_to(ctx.out(), "{} {} {}", t.type, t.lexeme, t.literal);
}