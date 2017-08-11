#pragma once

#include "common.h"

#include <string.h>

typedef size_t TokenIdType;
typedef struct TokenType_ TokenType;
struct TokenType_
{
    TokenIdType typeId;
    char const* typeStr;
    TokenType& operator=(TokenType const& other);
    bool operator==(TokenType const& rhs) const;
};

constexpr size_t const NA_TYPE_ID = 0;
constexpr size_t const EOF_TYPE_ID = 0;
constexpr TokenType const NA_TYPE { NA_TYPE_ID, "n/a"};
constexpr TokenType const EOF_TYPE { EOF_TYPE_ID, "EOF"};

class Token
{
public:
    Token() : Token(nullptr, NA_TYPE) {}
    Token(char const* text, TokenType const type) : Token(text, 0, type) {}
    Token(char const* text, size_t len, TokenType const type) : text(text), len(len), type(type) {}
    Token(Token const& other);

    Token& operator=(Token&& other);
    bool operator==(Token const& rhs) const;

    char const* getText() const { return text; }
    void getNullTerminatedText(char* buf, size_t buflen) const;
    size_t getLen() const { return len; }
    void setLen(size_t newLen) { len = newLen; }
    TokenType getType() const { return type; }

private:
    char const* text;
    size_t len;
    TokenType type;
};

