#include "basic_parser.h"
#include "print.h"

#include <cstdio>
#include <iostream>
#include <string>

static void readInput(char* buf, ssize_t const buf_size)
{
    ssize_t remain = buf_size;
    auto cur = buf;
    while(!std::cin.eof())
    {
        std::string line;
        std::getline(std::cin, line);
        if (line.length() > remain - 1)
        {
            break;
        }
        cur += std::snprintf(cur, remain, "%s", line.c_str());
        remain -= (line.length() + 1);
    }
}

int main(int argc, char* argv[])
{
    char buf[1024];
    readInput(buf, sizeof(buf));
    BasicLexer lexer(buf);
    BasicParser parser(lexer);
    BasicInterpreter interpreter;
    return RC_SUCCEEDED(parser.parse(interpreter)) ? 0 : 1;
}
