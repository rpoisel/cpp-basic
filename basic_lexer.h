#pragma once

#include "lexer.h"

#include <functional>
#include <vector>

constexpr TokenType const INTEGER_LITERAL_TYPE { 2, "INTEGER_LITERAL" };
constexpr TokenType const STRING_LITERAL_TYPE { 3, "STRING_LITERAL" };
constexpr TokenType const COMMA_TYPE { 4, "COMMA" };

constexpr TokenType const KEYWORDS[] {
    { 6, "PRINT" },
    { 7, "REM" },
    { 8, "GOTO" },
};

typedef std::function<bool (char)> CheckCb;

class BasicLexer : public Lexer<6>
{
public:
    static inline bool isWS(char const x) { return x  == ' ' || x == '\t' || x == '\n' || x == '\r'; }
    static inline bool isLetter(char const x) { return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z'; }
    static inline bool isDigit(char const x) { return x >= '0' && x <= '9'; }

    BasicLexer(char const* input) : Lexer(input) {}
    Token nextToken();
private:
    bool foresee(std::string const& keyword) const;

    void WS();
    Token GROUP(CheckCb cb, TokenType const tokenType);
    Token INTEGER_LITERAL();
    Token KEYWORD(TokenType const tokenType);
    Token STRING_LITERAL();
};
