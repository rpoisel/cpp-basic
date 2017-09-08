#pragma once

#include "basic_lexer.h"
#include "basic_interpreter_fwd.h"

namespace Lang
{
namespace Basic
{

class Command
{
public:
  constexpr Command(TokenIdType const& tokenId) :
      tokenId(tokenId)
  {
  }
  virtual RC execute(Interpreter* const interpreter) const = 0;
  constexpr TokenIdType const& getTokenId() const
  {
    return tokenId;
  }
private:
  TokenIdType const& tokenId;
};

class CommandRegistry
{
public:
  RC handleStatement(Interpreter* const interpreter) const;
};

extern const CommandRegistry commandRegistry;

}
}
