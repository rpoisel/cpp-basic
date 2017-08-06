#pragma once

#include "lexer.h"

#include <vector>

class BasicLexer : public Lexer
{
public:
    static inline bool isWS(char x) { return x  == ' ' || x == '\t' || x == '\n' || x == '\r'; }
    static inline bool isLetter(char x) { return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z'; }
    static inline bool isDigit(char x) { return x >= '0' && x <= '9'; }

    BasicLexer(std::istream& stream) : Lexer(stream) {}
    Token nextToken();
    std::string const& getTokenName(size_t idx);
private:
    void WS();
    Token NUM();
    Token NAME();
};
