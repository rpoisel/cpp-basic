#include "lexer.h"

#include <stdexcept>
#include <sstream>

TokenType& TokenType::operator=(TokenType const& other)
{
    this->typeId = other.typeId;
    this->typeStr = other.typeStr;

    return *this;
}

Token::Token(Token const& other)
{
    this->text = other.text;
    this->type = other.type;
}

Token& Token::operator=(Token&& other)
{
    this->text = other.text;
    this->type = other.type;

    return *this;
}

std::ostream & operator<<(std::ostream &os, Token const &token)
{ 
    return os << "\"" << token.text << "\" (" << token.type.typeStr << ")";
}

Lexer::Lexer(std::istream& input) : input(input)
{
    consume();
}

void Lexer::consume()
{
    if (input.eof())
    {
        current = EOF_CHAR;
        return;
    }
    current = input.get();
}

void Lexer::match(char x)
{
    if (current == x)
    {
        consume();
    }
    else
    {
        std::ostringstream errorMsg;
        errorMsg << "expecting " << x << ", found " << current;
        throw std::invalid_argument(errorMsg.str());
    }
}
