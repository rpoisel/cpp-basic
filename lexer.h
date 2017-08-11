#pragma once

#include "token.h"

#include <string.h>

template <int k>
class Lexer
{
public:
    Lexer(char const* input) : input(input), cur(input), end(input + std::strlen(input)) {}
    virtual ~Lexer() {}

    virtual RC nextToken(Token& token) = 0;

    RC match(char const x);
    RC match(char const* str, size_t& cnt);
    char const* LA(size_t i) const { return cur + i - 1 >= end ? end : cur + i - 1; }
    void consume();
private:

    char const* const input;
    char const* cur;
    char const* end;
};

template <int k>
void Lexer<k>::consume()
{
    if (cur == end)
    {
        return;
    }
    cur++;
}

template <int k>
RC Lexer<k>::match(char const x)
{
    if (*LA(1) == x)
    {
        consume();
        return RC_OK;
    }
    return RC_ERROR;
}

template <int k>
RC Lexer<k>::match(char const* str, size_t& cnt)
{
    cnt = 0;
    for (auto cur = str; *cur; cur++)
    {
        RC rc = match(*cur);
        if (RC_FAILED(rc))
        {
            return rc;
        }
        cnt++;
    }
    return RC_OK;
}
