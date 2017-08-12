#pragma once

#include "token.h"

#include <string.h>

class Lexer
{
public:
    Lexer(char const* input) : input(input), cur(input), end(input + ::strlen(input)) {}
    virtual ~Lexer() {}

    virtual RC nextToken(Token& token) = 0;

protected:

    RC match(char const x);
    RC match(char const* str, size_t& cnt);
    char const* LA(size_t i) const { return cur + i - 1 >= end ? end : cur + i - 1; }
    void consume();

private:
    char const* const input;
    char const* cur;
    char const* end;
};
