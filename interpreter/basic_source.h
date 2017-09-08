#pragma once

#include "lang_token.h"
#include "lang_source.h"

namespace Lang
{
namespace Basic
{

struct Line
{
  Line(char const* begin) :
      begin(begin), lenLineNo(0), lenLine(0), next(nullptr)
  {
  }
  char const* begin;
  size_t lenLineNo;
  size_t lenLine;
  Line* next;
};

class Source final : public Lang::Source
{
public:
  Source() :
      firstLine(nullptr), curLine(nullptr), curPosition(nullptr), terminator('\0')
  {
  }
  ~Source();
  RC add(char const* sourceFragment, size_t buflen);
  char const* LA(size_t i) const;
  RC set(char const* newPosition);
  RC jump(Token const& target);
  void consume();

private:
  RC add(Line* line);
  Line* firstLine;
  Line* curLine;
  char const* curPosition;
  char const terminator;
};

}
}
