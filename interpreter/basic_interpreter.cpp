#include "basic_interpreter.h"

BasicInterpreter::BasicInterpreter(char const* sourceCode, BasicFacilities& facilities)
    : lexer(sourceCode), lines(sourceCode), facilities(facilities), p(0)
{
    for (size_t idx = 0; idx < K; idx++)
    {
        consume();
    }
}

RC BasicInterpreter::run()
{
    RC rc;
    do
    {
        rc = line();
    } while (RC_SUCCEEDED(rc) && rc != RC_FINISH);
    return rc;
}

void BasicInterpreter::consume()
{
    lexer.nextToken(lookahead[p]);
    p = (p + 1) % K;
}

void BasicInterpreter::reset(char const* cur)
{
    lexer.reset(cur);

    p = 0;
    for (size_t idx = 0; idx < K; idx++)
    {
        consume();
    }
}

RC BasicInterpreter::match(TokenIdType const& tokenType)
{
    if (LA(1).getType() == tokenType)
    {
        consume();
        return RC_OK;
    }
    return RC_ERROR;
}

RC BasicInterpreter::line()
{
    if (LA(1).getType() == EOF_TYPE)
    {
        return RC_FINISH;
    }

    if (LA(1).getType() == INTEGER_LITERAL_TYPE)
    {
        consume();
    }
    RC rc = statement();
    if (RC_FAILED(rc) || rc == RC_CONTINUE)
    {
        return rc;
    }
    return match(NEWLINE_TYPE);
}

bool BasicInterpreter::condition(RC& rc)
{
    auto left = expression(rc);
    if (RC_FAILED(rc))
    {
        return false;
    }
    if (!isRelOp(1))
    {
        rc = RC_ERROR;
        return false;
    }
    auto relOp = LA(1).getType();
    consume();
    auto right = expression(rc);
    if (RC_FAILED(rc))
    {
        return false;
    }
    bool conditionResult;
    if (relOp == LT_TYPE)
    {
        conditionResult = left < right;
    }
    else if (relOp == LE_TYPE)
    {
        conditionResult = left <= right;
    }
    else if (relOp == GT_TYPE)
    {
        conditionResult = left > right;
    }
    else if (relOp == GE_TYPE)
    {
        conditionResult = left >= right;
    }
    else if (relOp == EQUAL_TYPE)
    {
        conditionResult = left == right;
    }
    else if (relOp == NEQ_TYPE)
    {
        conditionResult = left != right;
    }
    return conditionResult;
}

RC BasicInterpreter::statement()
{
    return basicCommandRegistry.handleStatement(this);
}

BasicVariant BasicInterpreter::expressionList(RC& rc)
{
    if (LA(1).getType() == STRING_LITERAL_TYPE)
    {
        BasicVariant result(LA(1).getText(), LA(1).getLen());
        consume();
        rc = RC_OK;
        return result;
    }
    return BasicVariant(expression(rc));
}

bool BasicInterpreter::isExpression(size_t offset) const
{
    return LA(1).getType() == PLUS_TYPE || LA(1).getType() == MINUS_TYPE || isTerm(offset);
}

ExpressionNumberValue BasicInterpreter::expression(RC& rc)
{
    if (!isExpression(1))
    {
        rc = RC_ERROR;
        return 0;
    }

    if (LA(1).getType() == PLUS_TYPE || LA(1).getType() == MINUS_TYPE)
    {
        consume();
    }
    auto result = term(rc);
    if (RC_FAILED(rc) || !isExpression(1))
    {
        return result;
    }
    if (LA(1).getType() == PLUS_TYPE)
    {
        return result + expression(rc);
    }
    return result - expression(rc);
}

bool BasicInterpreter::isTerm(size_t offset) const
{
    return isFactor(offset);
}

ExpressionNumberValue BasicInterpreter::term(RC& rc)
{
    auto result = factor(rc);
    if (RC_FAILED(rc))
    {
        return result;
    }
    if (LA(1).getType() == ASTERISK_TYPE && isFactor(2))
    {
        consume();
        return result * factor(rc);
    }
    if (LA(1).getType() == DIVIDER_TYPE && isFactor(2))
    {
        consume();
        return result / factor(rc);
    }
    return result;
}

bool BasicInterpreter::isFactor(size_t offset) const
{
    return LA(offset).getType() == VAR_TYPE || LA(offset).getType() == INTEGER_LITERAL_TYPE;
}

ExpressionNumberValue BasicInterpreter::factor(RC& rc)
{
    if (LA(1).getType() == VAR_TYPE)
    {
        char varName = *(LA(1)).getText();
        consume();
        if (BasicLexer::isUppercaseLetter(varName))
        {
            varName = (varName - 'A') + 'a';
        }
        rc = RC_OK;
        return variables[static_cast<size_t>(varName)];
    }
    if (LA(1).getType() == INTEGER_LITERAL_TYPE)
    {
        auto result = BasicVariant::toNumber(LA(1).getText(), LA(1).getLen());
        consume();
        rc = RC_OK;
        return result;
    }
    if (isExpression(1))
    {
        return expression(rc);
    }
    rc = RC_ERROR;
    return -1;
}

bool BasicInterpreter::isRelOp(size_t offset) const
{
    return LA(offset).getType() == LT_TYPE || LA(offset).getType() == LE_TYPE
        || LA(offset).getType() == GT_TYPE || LA(offset).getType() == GE_TYPE
        || LA(offset).getType() == EQUAL_TYPE || LA(offset).getType() == NEQ_TYPE;
}

char const* BasicInterpreter::searchLine(Token const& token) const
{
    if (!(LA(1).getType() == INTEGER_LITERAL_TYPE))
    {
        return nullptr;
    }
    return lines.search(token);
}
