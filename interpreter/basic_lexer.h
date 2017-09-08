#pragma once

#include "basic_token.h"
#include "basic_source.h"
#include "lang_lexer.h"

namespace Lang
{
namespace Basic
{

typedef bool (*CheckCb)(char);

class Lexer: public Lang::Lexer
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

  Lexer(Lang::Basic::Source& input) :
      Lang::Lexer(input), input(input)
  {
  }
  Lang::Token nextToken(RC& rc);
  inline RC jump(Lang::Token const& target)
  {
    return input.jump(target);
  }
private:
  bool foresee(char const* keyword) const;

  void WS();
  Lang::Token GROUP(CheckCb cb, Lang::TokenIdType const& tokenType);
  Lang::Token INTEGER_LITERAL();
  Lang::Token KEYWORD(Lang::Basic::KeywordTokenType const& tokenType);
  Lang::Token STRING_LITERAL();

  Lang::Basic::Source& input;
};

}
}
