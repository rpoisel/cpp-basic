#include "basic_lexer.h"
#include "print.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <cstring>

static void lexSourceCode(char const* sourceCode, std::vector<Token>& actualTokenIds)
{
  RC rc;
  BasicSource source;
  source.add(sourceCode, strlen(sourceCode));
  BasicLexer lexer(source);
  Token token = lexer.nextToken(rc);
  while (token.getType() != EOF_TYPE)
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
    std::vector<Token> expectedTokens
    {
      { sourceCode + 0, 2, INTEGER_LITERAL_TYPE},
      { sourceCode + 3, 5, PRINT_TYPE},
      { sourceCode + 10, 13, STRING_LITERAL_TYPE},
      { sourceCode + 24, 1, NEWLINE_TYPE}
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
    char const* sourceCode = "10 PRINT \"Hello, World!\"GOTO\n";
    std::vector<Token> expectedTokens
    {
      { sourceCode + 0, 2, INTEGER_LITERAL_TYPE},
      { sourceCode + 3, 5, PRINT_TYPE},
      { sourceCode + 10, 13, STRING_LITERAL_TYPE},
      { sourceCode + 24, 4, GOTO_TYPE},
      { sourceCode + 28, 1, NEWLINE_TYPE}
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
