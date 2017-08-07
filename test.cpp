#include "basic_lexer.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstring>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

static void parseSourceCode(char const* sourceCode, std::vector<TokenIdType>& actualTokenIds)
{
    BasicLexer lexer(sourceCode);
    Token token = lexer.nextToken();
    while(token.type.typeId != EOF_TYPE.typeId)
    {
        actualTokenIds.push_back(token.type.typeId);
        token = lexer.nextToken();
    }
}

SCENARIO("Parsing a print statement", "[basic]")
{
    GIVEN("Source code fragment")
    {
        std::vector<TokenIdType> expectedTokenIds {
            INTEGER_LITERAL_TYPE.typeId,
            KEYWORDS[0].typeId,
            STRING_LITERAL_TYPE.typeId,
        };
        WHEN ("only contains print statement")
        {
            THEN("List of tokens should be as expected")
            {
                std::vector<TokenIdType> actualTokenIds;
                parseSourceCode("10 PRINT \"Hello, World!\"", actualTokenIds);
                REQUIRE(expectedTokenIds == actualTokenIds);
            }
        }
        WHEN("also contains GOTO statement")
        {
            THEN("List of tokens should be as expected")
            {
                expectedTokenIds.push_back(KEYWORDS[2].typeId);
                std::vector<TokenIdType> actualTokenIds;
                parseSourceCode("10 PRINT \"Hello, World!\"GOTO", actualTokenIds);
                REQUIRE(expectedTokenIds == actualTokenIds);
            }
        }
    }
}
