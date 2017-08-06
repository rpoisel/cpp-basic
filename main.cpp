#include "basic_lexer.h"

#include <iostream>

int main(int argc, char* argv[])
{
    BasicLexer lexer(std::cin);
    Token token = lexer.nextToken();
    while(token.type.typeId != EOF_TYPE.typeId)
    {
        std::cout << token << std::endl;
        token = lexer.nextToken();
    }
    return 0;
}
