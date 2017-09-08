#include <basic_interpreter.h>
#include <arduino_facilities.h>

#include <Arduino.h>

#include <cstring>

constexpr char const* basic_prog PROGMEM
{
  "05 LET A = 0\n"
  //"06 LET B = 1\n"
  //"10 PRINT \"Hello, World!\"\n"
  //"15 PRINT 4 * 5 - 3 * 2\n"
  //"17 PRINT 15/5\n"
  "10 LET A = A + 1\n"
  "11 PRINT A\n"
  "12 PRINT \"\n\"\n"
  "13 LET Q = A / 2\n"
  "14 IF Q * 2 = A THEN PRINT \"EVEN\n\"\n"
  "15 IF Q * 2 <> A THEN PRINT \"ODD\n\"\n"
  "20 IF A <= 3 THEN GOTO 10\n"// TODO handle illegal GOTO targets
  "30 WHILE A > 0\n"
  "33 LET A = A - 1\n"
  "35 PRINT A\n"
  "40 PRINT \"\n\"\n"
  "45 IF A = 1 THEN GOTO 100\n"
  "50 WEND\n"
  "100 PRINT \"END\n\"\n"
};

void setup()
{
}

void loop()
{
  Lang::Basic::ArduinoFacilities facilities;
  Lang::Basic::Source source;
  source.add(basic_prog, ::strlen(basic_prog));
  Lang::Basic::Interpreter interpreter(source, facilities);
  interpreter.run();
}
