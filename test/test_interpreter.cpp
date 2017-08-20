#include "basic_interpreter.h"
#include "posix_facilities.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

SCENARIO("Interpreting a basic snippet", "[interpreter]")
{
    GIVEN("Source code fragment")
    {
        WHEN ("contains more than one line")
        {
            char const* sourceCode = \
                 "10 LET A = 1\n"
                 "20 WHILE A <= 5\n"
                 "30 PRINT A\n"
                 "40 PRINT \"\n\"\n"
                 "50 LET A = A + 1\n"
                 "60 WEND\n"
                 "70 PRINT \"END\n\"\n";
            THEN("List of tokens should be as expected")
            {
                PosixFacilities facilities;
                BasicInterpreter interpreter(sourceCode, facilities);
                RC rc = interpreter.run();
                REQUIRE(rc == RC_FINISH);
            }
        }
    }
}
