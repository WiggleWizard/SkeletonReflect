#pragma once


enum TokenType
{
	// Single-character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
	COLON,

	// One or two character tokens
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Preprocessor
	HASH,

	// Literals
	IDENTIFIER, STRING, NUMBER,

	// Keywords
	CLASS, CONST, STATIC,
	PUBLIC, PRIVATE,
	FOR, WHILE, IF, SWITCH,

	// Built in types
	INT, VOID, BOOL,

	// Reserved keywords for header tool
	MACRO_CLASS_DECL, MACRO_GEN_BODY,
	MACRO_FUNC_DECL, MACRO_PROP_DECL,

	END_OF_FILE
};