#pragma once

#include "list.h"
#include "token.h"

struct BasicLine
{
  BasicLine(char const* begin) :
      begin(begin), lenLineNo(0), lenLine(0), next(nullptr)
  {
  }
  char const* begin;
  size_t lenLineNo;
  size_t lenLine;
  BasicLine* next;
};

class BasicSource final
{
public:
  BasicSource() :
      firstLine(nullptr), curLine(nullptr), curPosition(nullptr), terminator('\0')
  {
  }
  ~BasicSource();
  RC add(char const* sourceFragment, size_t buflen);
  char const* LA(size_t i) const;
  RC set(char const* newPosition);
  RC jump(Token const& target);
  void consume();

private:
  RC add(BasicLine* line);
  BasicLine* firstLine;
  BasicLine* curLine;
  char const* curPosition;
  char const terminator;
};
