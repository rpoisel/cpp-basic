#pragma once

#include "basic_commands.h"
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

    void reset(char const* cur);
    void consume();
    RC match(TokenIdType const& tokenType);
    Token const& LA(size_t const i) const { return lookahead[(p + i - 1) % K]; }

    BasicFacilities& getFacilities() const { return facilities; }
    void setVarValue(size_t idx, ExpressionNumberValue value) { variables[idx] = value; }
    char const* searchLine(Token const& token) const;

    bool isExpression(size_t offset) const;

    RC line();
    RC statement();
    BasicVariant expressionList(RC& rc);
    ExpressionNumberValue expression(RC& rc);
    bool condition(RC& rc);

private:
    BasicLexer lexer;
    BasicLines lines;
    BasicFacilities& facilities;
    Token lookahead[K];
    size_t p;
    ExpressionNumberValue variables[26];

    bool isTerm(size_t offset) const;
    bool isFactor(size_t offset) const;
    bool isRelOp(size_t offset) const;

    ExpressionNumberValue term(RC& rc);
    ExpressionNumberValue factor(RC& rc);
};

