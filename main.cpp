#include "basic_lexer.h"
#include "parser.h"

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
    Token token = lexer.nextToken();
    while(token.type.typeId != EOF_TYPE.typeId)
    {
        std::cout << token << std::endl;
        token = lexer.nextToken();
    }
    return 0;
}
