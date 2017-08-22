#pragma once

#include "lexer.h"

constexpr TokenIdType const INTEGER_LITERAL_TYPE = 2;
constexpr TokenIdType const STRING_LITERAL_TYPE = 3;
constexpr TokenIdType const NEWLINE_TYPE = 4;
constexpr TokenIdType const PLUS_TYPE = 5;
constexpr TokenIdType const MINUS_TYPE = 6;
constexpr TokenIdType const ASTERISK_TYPE = 7;
constexpr TokenIdType const DIVIDER_TYPE = 8;
constexpr TokenIdType const VAR_TYPE = 9;
constexpr TokenIdType const EQUAL_TYPE = 10;
constexpr TokenIdType const LT_TYPE = 11;
constexpr TokenIdType const LE_TYPE = 12;
constexpr TokenIdType const GT_TYPE = 13;
constexpr TokenIdType const GE_TYPE = 14;
constexpr TokenIdType const NEQ_TYPE = 15;
constexpr TokenIdType const PRINT_TYPE = 0x80;
constexpr TokenIdType const REM_TYPE = 0x81;
constexpr TokenIdType const GOTO_TYPE = 0x82;
constexpr TokenIdType const LET_TYPE = 0x83;
constexpr TokenIdType const IF_TYPE = 0x84;
constexpr TokenIdType const THEN_TYPE = 0x85;
constexpr TokenIdType const WHILE_TYPE = 0x86;
constexpr TokenIdType const WEND_TYPE=0x87;

struct KeywordTokenType
{
    TokenIdType typeId;
    char const* typeStr;
};

constexpr size_t const PRINT_IDX = 0;
constexpr size_t const REM_IDX = 1;
constexpr size_t const GOTO_IDX = 2;
constexpr size_t const LET_IDX = 3;
constexpr size_t const IF_IDX = 4;
constexpr size_t const THEN_IDX = 5;
constexpr size_t const WHILE_IDX = 6;
constexpr size_t const WEND_IDX = 7;
constexpr KeywordTokenType const KEYWORDS[] {
    { PRINT_TYPE, "PRINT" },
    { REM_TYPE, "REM" },
    { GOTO_TYPE, "GOTO" },
    { LET_TYPE, "LET" },
    { IF_TYPE, "IF" },
    { THEN_TYPE, "THEN" },
    { WHILE_TYPE, "WHILE" },
    { WEND_TYPE, "WEND" },
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
    Token GROUP(CheckCb cb, TokenIdType const& tokenType);
    Token INTEGER_LITERAL();
    Token KEYWORD(KeywordTokenType const& tokenType);
    Token STRING_LITERAL();
};
