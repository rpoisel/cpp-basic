#pragma once

#include "basic_lexer.h"

constexpr size_t const K = 6;

class BasicParser
{
public:
    BasicParser(BasicLexer& lexer);
    RC parse();

protected:
    Token& LA(size_t i) { return lookahead[(p + i - 1) % K]; }
    RC match(TokenType const& tokenType);
    void consume();

private:
    BasicLexer& lexer;
    Token lookahead[K];
    size_t p;

    RC line();
    RC statement();
};
