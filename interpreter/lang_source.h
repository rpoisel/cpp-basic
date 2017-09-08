#pragma once

#include "lang_common.h"
#include <stddef.h>

namespace Lang
{

class Source
{
public:
  virtual ~Source()
  {
  }
  virtual char const* LA(size_t i) const = 0;
  virtual RC set(char const* newPosition) = 0;
  virtual void consume() = 0;
};

}
