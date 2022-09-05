#pragma once

#include "CommonDefs.h"

#include <EASTL/map.h>
#include <EASTL/string.h>


enum InternalTokenType
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
	K_CLASS, K_CONST, K_STATIC,
	K_PUBLIC, K_PRIVATE,
	FOR, WHILE, IF, SWITCH,

	// Built in types
	T_INT, T_VOID, T_BOOL,

	// Reserved keywords for header tool
	MACRO_CLASS_DECL, MACRO_GEN_BODY,
	MACRO_FUNC_DECL, MACRO_PROP_DECL,

	END_OF_INTERNAL_TYPES,

	START_OF_CUSTOM_TYPES,
	END_OF_CUSTOM_TYPES = 1024,

	END_OF_FILE
};

static ea::map<ea::string, InternalTokenType> StringToTokenTypeMap = {
	{ "LEFT_PAREN", LEFT_PAREN },
	{ "RIGHT_PAREN", RIGHT_PAREN },
	{ "LEFT_BRACE", LEFT_BRACE },
	{ "RIGHT_BRACE", RIGHT_BRACE },

	{ "COMMA", COMMA },
	{ "DOT", DOT },
	{ "MINUS", MINUS },
	{ "PLUS", PLUS },
	{ "SEMICOLON", SEMICOLON },
	{ "SLASH", SLASH },
	{ "STAR", STAR },
	{ "COLON", COLON },

	{ "BANG", BANG },
	{ "BANG_EQUAL", BANG_EQUAL },
	{ "EQUAL", EQUAL },
	{ "EQUAL_EQUAL", EQUAL_EQUAL },
	{ "GREATER", GREATER },
	{ "GREATER_EQUAL", GREATER_EQUAL },
	{ "LESS", LESS },
	{ "LESS_EQUAL", LESS_EQUAL },

	{ "HASH", HASH },

	{ "IDENTIFIER", IDENTIFIER },
	{ "STRING", STRING },
	{ "NUMBER", NUMBER },

	{ "K_CLASS", K_CLASS },
	{ "K_CONST", K_CONST },
	{ "K_STATIC", K_STATIC },
	{ "K_PUBLIC", K_PUBLIC },
	{ "K_PRIVATE", K_PRIVATE },
	{ "FOR", FOR },
	{ "WHILE", WHILE },
	{ "IF", IF },
	{ "SWITCH", SWITCH },

	{ "T_INT", T_INT },
	{ "T_VOID", T_VOID },
	{ "T_BOOL", T_BOOL },

	{ "MACRO_CLASS_DECL", MACRO_CLASS_DECL },
	{ "MACRO_GEN_BODY", MACRO_GEN_BODY },
	{ "MACRO_FUNC_DECL", MACRO_FUNC_DECL },
	{ "MACRO_PROP_DECL", MACRO_PROP_DECL },

	{ "END_OF_INTERNAL_TYPES", END_OF_INTERNAL_TYPES },

	{ "START_OF_CUSTOM_TYPES", START_OF_CUSTOM_TYPES },

	{ "END_OF_CUSTOM_TYPES", END_OF_CUSTOM_TYPES },

	{ "END_OF_FILE", END_OF_FILE }
};

template<typename T1, typename T2>
static inline ea::map<T2, T1> ReverseMap(ea::map<T1, T2> inMap)
{
	ea::map<T2, T1> result;
	for(const auto& element : inMap)
		result[element.second] = element.first;
	return result;
}

static ea::map<InternalTokenType, ea::string> TokenTypeToStringMap
	= ReverseMap<ea::string, InternalTokenType>(StringToTokenTypeMap);
