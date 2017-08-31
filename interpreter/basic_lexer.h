#pragma once

#include "basic_token.h"
#include "lexer.h"

typedef bool (*CheckCb)(char);

class BasicLexer: public Lexer
{
public:
  constexpr static inline bool isWS(char const x)
  {
    return x == ' ' || x == '\t' || x == '\r';
  }
  constexpr static inline bool isUppercaseLetter(char const x)
  {
    return x >= 'A' && x <= 'Z';
  }
  constexpr static inline bool isLowercaseLetter(char const x)
  {
    return x >= 'a' && x <= 'z';
  }
  constexpr static inline bool isLetter(char const x)
  {
    return isUppercaseLetter(x) || isLowercaseLetter(x);
  }
  constexpr static inline bool isDigit(char const x)
  {
    return x >= '0' && x <= '9';
  }

  BasicLexer(BasicSource& input) :
      Lexer(input)
  {
  }
  Token nextToken(RC& rc);
  inline RC jump(Token const& target)
  {
    return input.jump(target);
  }
private:
  bool foresee(char const* keyword) const;

  void WS();
  Token GROUP(CheckCb cb, TokenIdType const& tokenType);
  Token INTEGER_LITERAL();
  Token KEYWORD(KeywordTokenType const& tokenType);
  Token STRING_LITERAL();
};
