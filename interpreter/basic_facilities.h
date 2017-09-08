#pragma once

#include "lang_token.h"
#include "basic_variant.h"

namespace Lang
{
namespace Basic
{

class Facilities
{
public:
  virtual RC print(Lang::Token const& stringLiteral) = 0;
  virtual RC print(Lang::Basic::BasicVariant& variant) = 0;
  virtual RC print(char const* string, size_t len) = 0;
  virtual RC print(Lang::Basic::ExpressionNumberValue value) = 0;
};

}
}
