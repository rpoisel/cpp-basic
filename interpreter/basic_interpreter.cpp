#include "basic_interpreter.h"

RC BasicInterpreter::printStatement(Token const& stringLiteral)
{
    return RC_OK;
}

RC BasicInterpreter::gotoStatement(size_t lineNo, BasicLexer& lexer)
{
    return RC_OK;
}

RC BasicInterpreter::addJumplistEntry(size_t lineNo, char const* offset)
{
    return RC_OK;
}
