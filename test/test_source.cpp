#include "basic_source.h"
#include "basic_token.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

SCENARIO("Managing BASIC source code", "[source]")
{
  GIVEN("Source code fragment")
  { WHEN ("illegal line added")
  {
    THEN("")
    {
      BasicSource source;
      std::string line("line without newline char");
      REQUIRE(source.add(line.c_str(), line.length()) == RC_ERROR);
    }
  }
  WHEN ("only contains print statement")
  {
    std::string sourceCode("10 PRINT \"Hello, World!\"\n");
    THEN("BASIC source can be accessed as expected")
    {
      BasicSource source;
      source.add(sourceCode.c_str(), sourceCode.length());
      REQUIRE(*source.LA(1) == '1');
    }
  }
  WHEN ("contains several lines of source code")
  {
    THEN("should advance over line feeds as well")
    {
      BasicSource source;
      std::string line1("10 REM foo\n");
      std::string line2("20 PRINT \"bar\n\"\n");
      source.add(line1.c_str(), line1.length());
      source.add(line2.c_str(), line2.length());
      REQUIRE(*source.LA(1) == '1');
      source.consume();
      source.consume();
      REQUIRE(*source.LA(1) == ' ');
      REQUIRE(source.set(line2.c_str() + 3) == RC_OK);
      REQUIRE(*source.LA(1) == 'P');
    }
  }
  WHEN ("contains several lines in one c-string")
  {
    THEN("should handle line feeds correctly")
    {
      BasicSource source;
      std::string lines("10 REM foo\n20 PRINT \"foo\"\n");
      source.add(lines.c_str(), lines.length());
      for (size_t cnt = 0; cnt < lines.length(); cnt++)
      {
        REQUIRE(*source.LA(cnt + 1) == lines.at(cnt));
      }
    }
  }
  WHEN ("jump to existing target")
  {
    THEN("should result in success")
    {
      BasicSource source;
      std::string line1("10 REM foo\n");
      std::string line2("20 PRINT \"foo\"\n");
      std::string line3("30 JUMP\n");
      source.add(line1.c_str(), line1.length());
      source.add(line2.c_str(), line2.length());
      source.add(line3.c_str(), line3.length());
      Token jumpTarget("30", 2, INTEGER_LITERAL_TYPE);
      REQUIRE(source.jump(jumpTarget) == RC_OK);
      Token jumpTargetNotExisting("40", 2, INTEGER_LITERAL_TYPE);
      REQUIRE(source.jump(jumpTargetNotExisting) == RC_ERROR);
      REQUIRE(*source.LA(1) == ' ');
      REQUIRE(*source.LA(2) == 'J');
    }
  }
  WHEN ("contains unterminated string literal")
  {
    THEN ("should give an error")
    {
      BasicSource source;
      std::string line1("10 PRINT \"foo\n");
      std::string line2("20 REM comment\n");
      REQUIRE(source.add(line1.c_str(), line1.length()) == RC_ERROR);
      REQUIRE(source.add(line2.c_str(), line2.length()) == RC_OK);
      for (size_t cnt = 0; cnt < line2.length(); cnt++)
      {
        REQUIRE(*source.LA(cnt + 1) == line2.at(cnt));
      }
      std::string line3("30 PRINT \"first\" \"second\"\n");
      REQUIRE(source.add(line3.c_str(), line3.length()) == RC_OK);
      for (size_t cnt = 0; cnt < line3.length(); cnt++)
      {
        REQUIRE(*source.LA(cnt + line2.length() + 1) == line3.at(cnt));
      }
      std::string line4("30 WHILE\n");
      REQUIRE(source.add(line4.c_str(), line4.length()) == RC_OK);
      for (size_t cnt = 0; cnt < line4.length(); cnt++)
      {
        REQUIRE(*source.LA(cnt + line2.length() + line3.length() + 1) == line4.at(cnt));
      }
    }
  }
  WHEN ("dealing with strange strings")
  {
    THEN ("nothing dangerous should happen")
    {
      BasicSource source;
      char const* foo = "foo";
      REQUIRE(*source.LA(1) == '\0');
      REQUIRE(source.set(foo) == RC_ERROR);
      REQUIRE(source.add("", 0) == RC_ERROR);
      REQUIRE(source.add("\n\n\n", 3) == RC_OK);
      REQUIRE(*source.LA(1) == '\n');
      REQUIRE(*source.LA(2) == '\n');
      REQUIRE(*source.LA(3) == '\n');
      REQUIRE(*source.LA(4) == '\0');
      REQUIRE(*source.LA(5) == '\0');
      REQUIRE(source.set(foo) == RC_ERROR);
    }
  }
}
}
