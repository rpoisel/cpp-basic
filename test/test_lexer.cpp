#include "basic_lexer.h"
#include "print.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <cstring>

static void lexSourceCode(char const* sourceCode, std::vector<Lang::Token>& actualTokenIds)
{
  Lang::RC rc;
  Lang::Basic::Source source;
  source.add(sourceCode, strlen(sourceCode));
  Lang::Basic::Lexer lexer(source);
  Lang::Token token = lexer.nextToken(rc);
  while (token.getType() != Lang::EOF_TYPE)
  {
    actualTokenIds.push_back(token);
    token = lexer.nextToken(rc);
  }
}

SCENARIO("Parsing a print statement", "[lexer]")
{
  GIVEN("Source code fragment")
  { WHEN ("only contains print statement")
  {
    char const* sourceCode = "10 PRINT \"Hello, World!\"\n";
    std::vector<Lang::Token> expectedTokens
    {
      { sourceCode + 0, 2, Lang::Basic::INTEGER_LITERAL_TYPE},
      { sourceCode + 3, 5, Lang::Basic::PRINT_TYPE},
      { sourceCode + 10, 13, Lang::Basic::STRING_LITERAL_TYPE},
      { sourceCode + 24, 1, Lang::Basic::NEWLINE_TYPE}
    };
    THEN("List of tokens should be as expected")
    {
      std::vector<Lang::Token> actualTokens;
      lexSourceCode(sourceCode, actualTokens);
      REQUIRE(expectedTokens == actualTokens);
    }
  }
  WHEN("also contains GOTO statement")
  {
    char const* sourceCode = "10 PRINT \"Hello, World!\"GOTO\n";
    std::vector<Lang::Token> expectedTokens
    {
      { sourceCode + 0, 2, Lang::Basic::INTEGER_LITERAL_TYPE},
      { sourceCode + 3, 5, Lang::Basic::PRINT_TYPE},
      { sourceCode + 10, 13, Lang::Basic::STRING_LITERAL_TYPE},
      { sourceCode + 24, 4, Lang::Basic::GOTO_TYPE},
      { sourceCode + 28, 1, Lang::Basic::NEWLINE_TYPE}
    };
    THEN("List of tokens should be as expected")
    {
      std::vector<Lang::Token> actualTokens;
      lexSourceCode(sourceCode, actualTokens);
      REQUIRE(expectedTokens == actualTokens);
    }
  }
}
}
