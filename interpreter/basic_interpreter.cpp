#include "basic_interpreter.h"

namespace Lang
{
namespace Basic
{

Interpreter::Interpreter(Source& source, Facilities& facilities)
:
    lexer(source), facilities(facilities), p(0)
{
  prefillLookahead();
}

RC Interpreter::run()
{
  RC rc;
  do
  {
    rc = line();
  } while (RC_SUCCEEDED(rc) && rc != RC_FINISH);
  return rc;
}

void Interpreter::consume()
{
  RC rc;
  lookahead[p] = lexer.nextToken(rc);
  p = (p + 1) % K;
}

void Interpreter::reset(char const* cur)
{
  lexer.reset(cur);

  p = 0;
  prefillLookahead();
}

RC Interpreter::match(TokenIdType const& tokenType)
{
  if (LA(1).getType() == tokenType)
  {
    consume();
    return RC_OK;
  }
  return RC_ERROR;
}

RC Interpreter::line()
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

bool Interpreter::condition(RC& rc)
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

RC Interpreter::statement()
{
  return commandRegistry.handleStatement(this);
}

BasicVariant Interpreter::expressionList(RC& rc)
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

RC Interpreter::jump(Token const& target)
{
  RC rc = lexer.jump(target);
  if (RC_FAILED(rc))
  {
    return rc;
  }
  prefillLookahead();
  return RC_OK;
}

bool Interpreter::isExpression(size_t offset) const
    {
  return LA(1).getType() == PLUS_TYPE || LA(1).getType() == MINUS_TYPE || isTerm(offset);
}

ExpressionNumberValue Interpreter::expression(RC& rc)
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

bool Interpreter::isTerm(size_t offset) const
    {
  return isFactor(offset);
}

ExpressionNumberValue Interpreter::term(RC& rc)
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

bool Interpreter::isFactor(size_t offset) const
    {
  return LA(offset).getType() == VAR_TYPE || LA(offset).getType() == INTEGER_LITERAL_TYPE;
}

ExpressionNumberValue Interpreter::factor(RC& rc)
{
  if (LA(1).getType() == VAR_TYPE)
  {
    char varName = *(LA(1)).getText();
    consume();
    ExpressionNumberValue retVal;
    rc = getVarValue(varName, retVal);
    return retVal;
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

bool Interpreter::isRelOp(size_t offset) const
    {
  return LA(offset).getType() == LT_TYPE || LA(offset).getType() == LE_TYPE
      || LA(offset).getType() == GT_TYPE || LA(offset).getType() == GE_TYPE
      || LA(offset).getType() == EQUAL_TYPE || LA(offset).getType() == NEQ_TYPE;
}

}
}
