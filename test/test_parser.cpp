#include "basic_parser.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

SCENARIO("Parsing a basic snippet", "[parser]")
{
    GIVEN("Source code fragment")
    {
        WHEN ("contains more than one line")
        {
            char const* sourceCode = \
                 "10 PRINT \"Hello, World!\"\n"
                 "20 GOTO 10\n";
            THEN("List of tokens should be as expected")
            {
                BasicLexer lexer(sourceCode);
                BasicParser parser(lexer);
                RC rc = parser.parse();
                REQUIRE(rc == RC_FINISH);
            }
        }
    }
}
