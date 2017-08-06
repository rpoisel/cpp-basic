#pragma once

#include <cstdlib>
#include <istream>
#include <ostream>
#include <string>

typedef struct _TokenType TokenType;
struct _TokenType
{
    TokenType& operator=(TokenType const& other);
    size_t typeId;
    char const* typeStr;
};

TokenType const NA_TYPE = { 0, "n/a" };
TokenType const EOF_TYPE = { 1, "EOF" };

constexpr char const EOF_CHAR = -1;

class Token
{
public:
    Token(char const* te, TokenType ty) : text(te), type(ty) {}
    Token(Token const& other);

    Token& operator=(Token&& other);

    std::string text;
    TokenType type;
};
std::ostream & operator<<(std::ostream &os, Token const &token);

class Lexer
{
public:
    Lexer(std::istream& input);
    virtual ~Lexer() {}

    virtual Token nextToken() = 0;

    char peek() { return current; }
    bool eof() const { return input.eof(); }
    void consume();
    void match(char x);
private:
    std::istream& input;
    char current;
};
