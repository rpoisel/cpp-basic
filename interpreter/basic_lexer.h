#pragma once

#include "lexer.h"

constexpr size_t const INTEGER_LITERAL_TYPE_ID = 2;
constexpr size_t const STRING_LITERAL_TYPE_ID = 3;
constexpr size_t const NEWLINE_TYPE_ID = 4;
constexpr size_t const PRINT_TYPE_ID = 5;
constexpr size_t const REM_TYPE_ID = 6;
constexpr size_t const GOTO_TYPE_ID = 7;
constexpr TokenType const INTEGER_LITERAL_TYPE { INTEGER_LITERAL_TYPE_ID, "INTEGER_LITERAL" };
constexpr TokenType const STRING_LITERAL_TYPE { STRING_LITERAL_TYPE_ID, "STRING_LITERAL" };
constexpr TokenType const NEWLINE_TYPE { NEWLINE_TYPE_ID, "COMMA" };

constexpr size_t const PRINT_IDX = 0;
constexpr size_t const REM_IDX = 1;
constexpr size_t const GOTO_IDX = 2;
constexpr TokenType const KEYWORDS[] {
    { PRINT_TYPE_ID, "PRINT" },
    { REM_TYPE_ID, "REM" },
    { GOTO_TYPE_ID, "GOTO" },
};

typedef bool (*CheckCb)(char);

class BasicLexer : public Lexer
{
public:
    static inline bool isWS(char const x) { return x  == ' ' || x == '\t' || x == '\r'; }
    static inline bool isLetter(char const x) { return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'); }
    static inline bool isDigit(char const x) { return x >= '0' && x <= '9'; }

    BasicLexer(char const* input) : Lexer(input) {}
    RC nextToken(Token& token);
private:
    bool foresee(char const* keyword) const;

    void WS();
    Token GROUP(CheckCb cb, TokenType const tokenType);
    Token INTEGER_LITERAL();
    Token KEYWORD(TokenType const tokenType);
    Token STRING_LITERAL();
};
