#pragma once

#include "lang_token.h"

namespace Lang
{
namespace Basic
{

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
constexpr TokenIdType const WEND_TYPE = 0x87;

struct KeywordTokenType
{
  TokenIdType typeId;
  char const* typeStr;
};

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

}
}
