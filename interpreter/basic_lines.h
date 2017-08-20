#pragma once

#include "basic_lexer.h"
#include "list.h"
#include "token.h"

class BasicLines
{
public:
    BasicLines(char const* sourceCode);

    char const* search(Token const& jumpTarget);
private:
    struct BasicLine
    {
        BasicLine(char const* begin) : begin(begin), lenLineNo(0), lenLine(0) {}
        char const* begin;
        size_t lenLineNo;
        size_t lenLine;
    };

    void parse(char const* sourceCode);
    List<BasicLine> lines;
};
