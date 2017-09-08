#pragma once

#include "lang_source.h"
#include "lang_token.h"

namespace Lang
{
class Lexer
{
public:
  Lexer(Source& input) :
      input(input)
  {
  }
  virtual ~Lexer()
  {
  }

  virtual Token nextToken(RC& rc) = 0;

  inline char const* LA(size_t i) const
      {
    return input.LA(i);
  }
  inline void reset(char const* newCur)
  {
    input.set(newCur);
  }

protected:
  RC match(char const x);
  RC match(char const* str, size_t& cnt);
  inline void consume()
  {
    input.consume();
  }

private:
  Source& input;
};
}
