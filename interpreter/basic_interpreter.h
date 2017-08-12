#pragma once

#include "basic_lexer.h"

class BasicParser;

class BasicInterpreter
{
public:
    RC addJumplistEntry(size_t lineNo, char const* offset);
    RC printStatement(Token const& stringLiteral);
    RC gotoStatement(size_t lineNo, BasicLexer& lexer);

public:
    // platform dependent print, draw, etc. facilities
    // jumplist
};

