#include "basic_interpreter.h"
#include "posix_facilities.h"

#include <cstdio>
#include <iostream>
#include <string>

#if 0
static void readInput(char* buf, ssize_t const buf_size)
{
  ssize_t remain = buf_size;
  auto cur = buf;
  while(!std::cin.eof())
  {
    std::string line;
    std::getline(std::cin, line);
    if (static_cast<ssize_t>(line.length()) > remain - 1)
    {
      break;
    }
    cur += std::snprintf(cur, remain, "%s", line.c_str());
    remain -= (line.length() + 1);
  }
}
#endif

int main(void)
{
  constexpr char const* sourceCode =
      "05 LET A = 0\n"
      //"06 LET B = 1\n"
      //"10 PRINT \"Hello, World!\"\n"
      //"15 PRINT 4 * 5 - 3 * 2\n"
      //"17 PRINT 15/5\n"
          "10 LET A = A + 1\n"
          "11 PRINT \"A = \"\n"
          "12 PRINT A\n"
          "13 LET Q = A / 2\n"
          "14 IF Q * 2 = A THEN PRINT \" (EVEN)\n\"\n"
          "15 IF Q * 2 <> A THEN PRINT \" (ODD)\n\"\n"
          "20 IF A <= 3 THEN GOTO 10\n"// TODO handle illegal GOTO targets
          "30 WHILE A > 0\n"
          "33 LET A = A - 1\n"
          "34 PRINT \"A = \"\n"
          "35 PRINT A\n"
          "40 PRINT \"\n\"\n"
          "41 LET B = 2\n"
          "42 WHILE B > 0\n"
          "43 PRINT \"B = \"\n"
          "44 PRINT A + B * 2 + 1\n"
          "45 PRINT \"\n\"\n"
          "46 LET B = B - 1\n"
          "50 WEND\n"
          "60 IF A = 1 THEN GOTO 80\n"
          "70 WEND\n"
          "80 REM This should be ignored.\n"
          "100 PRINT \"END\n\"\n";
  PosixFacilities facilities;
  BasicSource source;
  source.add(sourceCode, ::strlen(sourceCode));
  BasicInterpreter interpreter(source, facilities);
  return RC_SUCCEEDED(interpreter.run()) ? 0 : 1;
}
