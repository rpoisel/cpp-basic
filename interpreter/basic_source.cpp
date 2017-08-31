#include "basic_source.h"
#include "basic_token.h"

#include <string.h>

BasicSource::~BasicSource()
{
  auto line = firstLine;
  while (line)
  {
    auto oldline = line;
    line = line->next;
    delete oldline;
  }
}

RC BasicSource::add(char const* sourceFragment, size_t len)
{
  if (sourceFragment[len - 1] != '\n')
  {
    return RC_ERROR;
  }

  auto cur = sourceFragment;

  while (*cur)
  {
    auto line = new BasicLine(cur);
    bool parsingLineNo = true;
    if (!line)
    {
      return RC_ERROR;
    }

    for (;;)
    {
      if (parsingLineNo)
      {
        if (*cur >= '0' && *cur <= '9')
        {
          line->lenLineNo++;
        }
        else
        {
          parsingLineNo = false;
        }
      }
      if (*cur == '\"')
      {
        cur++;
        while (*cur != '\"' && *cur != '\0')
        {
          cur++;
        }
        if (*cur != '\"')
        {
          delete line;
          return RC_ERROR;
        }
      }
      if (*cur == '\n')
      {
        cur++;
        break;
      }
      cur++;
    }

    line->lenLine = cur - line->begin;
    RC rc = add(line);
    if (RC_FAILED(rc))
    {
      delete line;
      return rc;
    }
  }
  return RC_OK;
}

RC BasicSource::add(BasicLine* line)
{
  if (!firstLine)
  {
    firstLine = line;
    curLine = firstLine;
    curPosition = curLine->begin;
    return RC_OK;
  }

  auto writeLine = firstLine;
  while (writeLine->next)
  {
    writeLine = writeLine->next;
  }
  writeLine->next = line;
  return RC_OK;
}

char const* BasicSource::LA(size_t i) const
    {
  if (!curLine || !*curPosition)
  {
    return &terminator;
  }
  auto line = curLine;
  auto cur = curPosition;
  auto cnt = i;
  while (cnt > 1)
  {
    if (!*cur || *cur == '\n')
    {
      line = line->next;
      if (!line)
      {
        return &terminator;
      }
      cur = line->begin;
      cnt--;
      continue;
    }
    cur++;
    cnt--;
  }
  return cur;
}

RC BasicSource::set(char const* newPosition)
{
  auto line = firstLine;
  while (line)
  {
    if (newPosition >= line->begin && newPosition <= line->begin + line->lenLine)
    {
      curLine = line;
      curPosition = newPosition;
      return RC_OK;
    }
    line = line->next;
  }
  return RC_ERROR; /* not found */
}

RC BasicSource::jump(Token const& target)
{
  if (!(target.getType() == INTEGER_LITERAL_TYPE))
  {
    return RC_ERROR;
  }
  auto line = firstLine;
  while (line)
  {
    if (line->lenLineNo == target.getLen() &&
        !strncmp(line->begin, target.getText(), line->lenLineNo))
    {
      curLine = line;
      curPosition = line->begin + line->lenLineNo;
      return RC_OK;
    }
    line = line->next;
  }
  return RC_ERROR; /* target not found */
}

void BasicSource::consume()
{
  if (*curPosition)
  {
    curPosition++;
    return;
  }
  curLine = curLine->next;
  if (!curLine)
  {
    return;
  }
  curPosition = curLine->begin;
}
