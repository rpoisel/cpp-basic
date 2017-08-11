#include "basic_lexer.h"
#include "print.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

static void parseSourceCode(char const* sourceCode, std::vector<Token>& actualTokenIds)
{
    BasicLexer lexer(sourceCode);
    Token token;
    lexer.nextToken(token);
    while(token.getType().typeId != EOF_TYPE.typeId)
    {
        actualTokenIds.push_back(token);
        lexer.nextToken(token);
    }
}

SCENARIO("Parsing a print statement", "[basic]")
{
    GIVEN("Source code fragment")
    {
        WHEN ("only contains print statement")
        {
            char const* sourceCode = "10 PRINT \"Hello, World!\"";
            std::vector<Token> expectedTokens {
                { sourceCode + 0,  2,  INTEGER_LITERAL_TYPE },
                { sourceCode + 3,  5,  KEYWORDS[0] },
                { sourceCode + 10, 13, STRING_LITERAL_TYPE }
            };
            THEN("List of tokens should be as expected")
            {
                std::vector<Token> actualTokens;
                parseSourceCode(sourceCode, actualTokens);
                REQUIRE(expectedTokens == actualTokens);
            }
        }
        WHEN("also contains GOTO statement")
        {
            char const* sourceCode = "10 PRINT \"Hello, World!\"GOTO";
            std::vector<Token> expectedTokens {
                { sourceCode + 0,  2,  INTEGER_LITERAL_TYPE },
                { sourceCode + 3,  5,  KEYWORDS[0] },
                { sourceCode + 10, 13, STRING_LITERAL_TYPE },
                { sourceCode + 24, 4,  KEYWORDS[2] }
            };
            THEN("List of tokens should be as expected")
            {
                std::vector<Token> actualTokens;
                parseSourceCode(sourceCode, actualTokens);
                REQUIRE(expectedTokens == actualTokens);
            }
        }
    }
}
