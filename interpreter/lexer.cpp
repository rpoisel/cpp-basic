#include "lexer.h"

void Lexer::consume()
{
    if (cur == end)
    {
        return;
    }
    cur++;
}

RC Lexer::match(char const x)
{
    if (*LA(1) == x)
    {
        consume();
        return RC_OK;
    }
    return RC_ERROR;
}

RC Lexer::match(char const* str, size_t& cnt)
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
