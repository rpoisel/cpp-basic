#include <basic_parser.h>
#include <basic_interpreter.h>

#include <Arduino.h>

constexpr char const* basic_prog {
    "10 PRINT \"Hello, World!\""
};

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    BasicLexer lexer(basic_prog);
    BasicParser parser(lexer);
    BasicInterpreter interpreter;
    parser.parse(interpreter);
}
