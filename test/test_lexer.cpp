#include "basic_lexer.h"
#include "print.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

static void lexSourceCode(char const* sourceCode, std::vector<Token>& actualTokenIds)
{
    RC rc;
    BasicLexer lexer(sourceCode);
    Token token = lexer.nextToken(rc);
    while(token.getType() != EOF_TYPE)
    {
        actualTokenIds.push_back(token);
        token = lexer.nextToken(rc);
    }
}

SCENARIO("Parsing a print statement", "[lexer]")
{
    GIVEN("Source code fragment")
    {
        WHEN ("only contains print statement")
        {
            char const* sourceCode = "10 PRINT \"Hello, World!\"";
            std::vector<Token> expectedTokens {
                { sourceCode + 0,  2,  INTEGER_LITERAL_TYPE },
                { sourceCode + 3,  5,  PRINT_TYPE },
                { sourceCode + 10, 13, STRING_LITERAL_TYPE }
            };
            THEN("List of tokens should be as expected")
            {
                std::vector<Token> actualTokens;
                lexSourceCode(sourceCode, actualTokens);
                REQUIRE(expectedTokens == actualTokens);
            }
        }
        WHEN("also contains GOTO statement")
        {
            char const* sourceCode = "10 PRINT \"Hello, World!\"GOTO";
            std::vector<Token> expectedTokens {
                { sourceCode + 0,  2,  INTEGER_LITERAL_TYPE },
                { sourceCode + 3,  5,  PRINT_TYPE },
                { sourceCode + 10, 13, STRING_LITERAL_TYPE },
                { sourceCode + 24, 4,  GOTO_TYPE }
            };
            THEN("List of tokens should be as expected")
            {
                std::vector<Token> actualTokens;
                lexSourceCode(sourceCode, actualTokens);
                REQUIRE(expectedTokens == actualTokens);
            }
        }
    }
}
