#include "basic_interpreter.h"
#include "posix_facilities.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstring>

SCENARIO("Interpreting a basic snippet", "[interpreter]")
{
  GIVEN("Source code fragment")
  { WHEN ("contains more than one line")
  {
    char const* sourceCode =
    "10 LET A = 1\n"
    "15 LET B = B + 1\n"
    "20 WHILE A <= 5\n"
    "30 PRINT A\n"
    "40 PRINT \"\n\"\n"
    "50 LET A = A + 1\n"
    "60 WEND\n"
    "70 PRINT \"END\n\"\n";
    THEN("List of tokens should be as expected")
    {
      PosixFacilities facilities;
      BasicSource source;
      source.add(sourceCode, ::strlen(sourceCode));
      BasicInterpreter interpreter(source, facilities);
      REQUIRE(interpreter.setVarValue('B', 42) == RC_OK);
      REQUIRE(interpreter.setVarValue(213, 42) == RC_ERROR);
      REQUIRE(interpreter.run() == RC_FINISH);
      ExpressionNumberValue varVal;
      REQUIRE(interpreter.getVarValue('A', varVal) == RC_OK);
      REQUIRE(varVal == 6);
      REQUIRE(interpreter.getVarValue('B', varVal) == RC_OK);
      REQUIRE(varVal == 43);
    }
  }
}
}
