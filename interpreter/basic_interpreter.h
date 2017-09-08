#pragma once

#include "basic_commands.h"
#include "basic_facilities.h"
#include "basic_lexer.h"
#include "basic_source.h"
#include "basic_variant.h"

constexpr size_t const K = 6;

namespace Lang
{
namespace Basic
{

class Interpreter
{
public:
  Interpreter(Source& source, Facilities& facilities);
  RC run();

  void reset(char const* cur);
  void consume();
  RC match(TokenIdType const& tokenType);
  Token const& LA(size_t const i) const
      {
    return lookahead[(p + i - 1) % K];
  }

  Facilities& getFacilities() const
  {
    return facilities;
  }
  RC jump(Token const& target);

  bool isExpression(size_t offset) const;

  RC line();
  RC statement();
  BasicVariant expressionList(RC& rc);
  ExpressionNumberValue expression(RC& rc);
  bool condition(RC& rc);

  inline RC getVarValue(char varName, ExpressionNumberValue& value) const
      {
    char normalizedName = getNormalizedName(varName);
    if (!isValidVarName(normalizedName))
    {
      return RC_ERROR;
    }
    value = variables[static_cast<size_t>(normalizedName)];
    return RC_OK;
  }
  inline RC setVarValue(char varName, ExpressionNumberValue const& value)
  {
    char normalizedName = getNormalizedName(varName);
    if (!isValidVarName(normalizedName))
    {
      return RC_ERROR;
    }
    variables[static_cast<size_t>(normalizedName)] = value;
    return RC_OK;
  }
  inline void prefillLookahead()
  {
    for (size_t idx = 0; idx < K; idx++)
    {
      consume();
    }
  }

private:
  Lexer lexer;
  Facilities& facilities;
  Token lookahead[K];
  size_t p;
  ExpressionNumberValue variables[26];

  bool isTerm(size_t offset) const;
  bool isFactor(size_t offset) const;
  bool isRelOp(size_t offset) const;

  ExpressionNumberValue term(RC& rc);
  ExpressionNumberValue factor(RC& rc);

  inline static char getNormalizedName(char varName)
  {
    return Lexer::isLowercaseLetter(varName) ?
                                                    (varName - 'a') + 'A' :
                                                    varName;
  }
  inline static bool isValidVarName(char varName)
  {
    return varName >= 'A' && varName <= 'Z';
  }
};

}
}
