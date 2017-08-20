#pragma once

#include "lexer.h"

constexpr size_t const INTEGER_LITERAL_TYPE_ID = 2;
constexpr size_t const STRING_LITERAL_TYPE_ID = 3;
constexpr size_t const NEWLINE_TYPE_ID = 4;
constexpr size_t const PLUS_TYPE_ID = 5;
constexpr size_t const MINUS_TYPE_ID = 6;
constexpr size_t const ASTERISK_TYPE_ID = 7;
constexpr size_t const DIVIDER_TYPE_ID = 8;
constexpr size_t const VAR_TYPE_ID = 9;
constexpr size_t const EQUAL_TYPE_ID = 10;
constexpr size_t const LT_TYPE_ID = 11;
constexpr size_t const LE_TYPE_ID = 12;
constexpr size_t const GT_TYPE_ID = 13;
constexpr size_t const GE_TYPE_ID = 14;
constexpr size_t const NEQ_TYPE_ID = 15;
constexpr size_t const PRINT_TYPE_ID = 0x80;
constexpr size_t const REM_TYPE_ID = 0x81;
constexpr size_t const GOTO_TYPE_ID = 0x82;
constexpr size_t const LET_TYPE_ID = 0x83;
constexpr size_t const IF_TYPE_ID = 0x84;
constexpr size_t const THEN_TYPE_ID = 0x85;
constexpr size_t const WHILE_TYPE_ID = 0x86;
constexpr size_t const WEND_TYPE_ID=0x87;

constexpr TokenType const INTEGER_LITERAL_TYPE { INTEGER_LITERAL_TYPE_ID, "INTEGER_LITERAL" };
constexpr TokenType const STRING_LITERAL_TYPE { STRING_LITERAL_TYPE_ID, "STRING_LITERAL" };
constexpr TokenType const NEWLINE_TYPE { NEWLINE_TYPE_ID, "NEWLINE" };
constexpr TokenType const PLUS_TYPE { PLUS_TYPE_ID, "PLUS" };
constexpr TokenType const MINUS_TYPE { MINUS_TYPE_ID, "MINUS" };
constexpr TokenType const ASTERISK_TYPE { ASTERISK_TYPE_ID, "ASTERISK" };
constexpr TokenType const DIVIDER_TYPE { DIVIDER_TYPE_ID, "DIVIDER" };
constexpr TokenType const VAR_TYPE { VAR_TYPE_ID, "VAR" };
constexpr TokenType const EQUAL_TYPE { EQUAL_TYPE_ID, "EQUAL" };
constexpr TokenType const LT_TYPE { LT_TYPE_ID, "LESS THAN" };
constexpr TokenType const LE_TYPE { LE_TYPE_ID, "LESS THEN OR EQUAL" };
constexpr TokenType const GT_TYPE { GT_TYPE_ID, "GREATER THAN" };
constexpr TokenType const GE_TYPE { GE_TYPE_ID, "GREATER THAN OR EQUAL" };
constexpr TokenType const NEQ_TYPE { NEQ_TYPE_ID, "NOT EQUAL" };

constexpr size_t const PRINT_IDX = 0;
constexpr size_t const REM_IDX = 1;
constexpr size_t const GOTO_IDX = 2;
constexpr size_t const LET_IDX = 3;
constexpr size_t const IF_IDX = 4;
constexpr size_t const THEN_IDX = 5;
constexpr size_t const WHILE_IDX = 6;
constexpr size_t const WEND_IDX = 7;
constexpr TokenType const KEYWORDS[] {
    { PRINT_TYPE_ID, "PRINT" },
    { REM_TYPE_ID, "REM" },
    { GOTO_TYPE_ID, "GOTO" },
    { LET_TYPE_ID, "LET" },
    { IF_TYPE_ID, "IF" },
    { THEN_TYPE_ID, "THEN" },
    { WHILE_TYPE_ID, "WHILE" },
    { WEND_TYPE_ID, "WEND" },
};

typedef bool (*CheckCb)(char);

class BasicLexer : public Lexer
{
public:
    constexpr static inline bool isWS(char const x) { return x  == ' ' || x == '\t' || x == '\r'; }
    constexpr static inline bool isUppercaseLetter(char const x) { return x >= 'A' && x <= 'Z'; }
    constexpr static inline bool isLowercaseLetter(char const x) { return x >= 'a' && x <= 'z'; }
    constexpr static inline bool isLetter(char const x) { return isUppercaseLetter(x) || isLowercaseLetter(x); }
    constexpr static inline bool isDigit(char const x) { return x >= '0' && x <= '9'; }

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
