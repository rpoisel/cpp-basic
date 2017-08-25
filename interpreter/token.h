#pragma once

#include "basic_common.h"

#include <string.h>

typedef int16_t TokenIdType;
constexpr TokenIdType const NA_TYPE =   0;
constexpr TokenIdType const EOF_TYPE = -1;

class Token
{
public:
    Token() : Token(nullptr, NA_TYPE) {}
    Token(char const* text, TokenIdType const type) : Token(text, 0, type) {}
    Token(char const* text, size_t len, TokenIdType const type) : text(text), len(len), type(type) {}
    Token(Token const& other);

    Token& operator=(Token&& other);
    Token& operator=(Token const& other);
    bool operator==(Token const& rhs) const;

    char const* getText() const { return text; }
    void getNullTerminatedText(char* buf, size_t buflen) const;
    size_t getLen() const { return len; }
    TokenIdType getType() const { return type; }

private:
    char const* text;
    size_t len;
    TokenIdType type;
};

