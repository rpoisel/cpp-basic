#include "basic_lines.h"

#include <string.h>

BasicLines::BasicLines(char const* sourceCode)
{
    parse(sourceCode);
}

void BasicLines::parse(char const* sourceCode)
{
    bool parsingLineNo = true;
    auto curLine = BasicLine(sourceCode);
    for (auto cur = sourceCode; *cur; cur++)
    {
        if (parsingLineNo)
        {
            if (*cur >= '0' && *cur <= '9')
            {
                curLine.lenLineNo++;
            }
            else
            {
                parsingLineNo = false;
            }
        }
        if (*cur != '\n')
        {
            curLine.lenLine++;
            continue;
        }

        lines.add(curLine);
        parsingLineNo = true;
        curLine = BasicLine(cur + 1);
    }
    if (curLine.lenLine > 0)
    {
        lines.add(curLine);
    }
}

char const* BasicLines::search(Token const& jumpTarget)
{
    if (!(jumpTarget.getType() == INTEGER_LITERAL_TYPE))
    {
        return nullptr;
    }

    for (auto it = lines.getIterator();it.hasNext();)
    {
        auto line = it.next();
        if (line.lenLineNo != jumpTarget.getLen())
        {
            continue;
        }
        if (!strncmp(line.begin, jumpTarget.getText(), line.lenLineNo))
        {
            return line.begin;
        }
    }

    return nullptr;
}
