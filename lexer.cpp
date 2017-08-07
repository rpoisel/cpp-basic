#include "lexer.h"

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
