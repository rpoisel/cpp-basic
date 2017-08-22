#pragma once

#include "basic_facilities.h"
#include "basic_lexer.h"
#include "basic_lines.h"
#include "basic_variant.h"

constexpr size_t const K = 6;

class BasicInterpreter
{
public:
    BasicInterpreter(char const* sourceCode, BasicFacilities& facilities);
    RC run();
    BasicLexer& getLexer() { return lexer; }

    void setCur(char const* cur);

protected:
    Token& LA(size_t i) { return lookahead[(p + i - 1) % K]; }
    RC match(TokenIdType const& tokenType);
    void consume();

private:
    BasicLexer lexer;
    BasicLines lines;
    BasicFacilities& facilities;
    Token lookahead[K];
    size_t p;
    ExpressionNumberValue variables[26];

    RC line();
    RC statement();
    RC print_statement();
    RC if_statement();
    RC while_statement();
    RC goto_statement();
    RC let_statement();
    bool condition(RC& rc);
    BasicVariant expressionList(RC& rc);
    ExpressionNumberValue expression(RC& rc);
    ExpressionNumberValue term(RC& rc);
    ExpressionNumberValue factor(RC& rc);

    bool isExpression(size_t offset);
    bool isTerm(size_t offset);
    bool isFactor(size_t offset);
    bool isRelOp(size_t offset);
};
