#pragma once

#include "basic_source.h"
#include "token.h"

class Lexer
{
public:
  Lexer(BasicSource& input) :
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
  BasicSource& input;
};
