#include "basic_lexer.h"

#include <sstream>

TokenType const NUM_TYPE = { 2, "NUM" };
TokenType const NAME_TYPE = { 3, "NAME" };
TokenType const QUOTE_TYPE = { 4, "QUOTE" };
TokenType const COMMA_TYPE = { 5, "COMMA" };
TokenType const EXCL_MARK_TYPE = { 6, "EXCL_MARK" };

Token BasicLexer::nextToken()
{
    while(!eof())
    {
        if (isWS(peek()))
        {
            WS();
            continue;
        }
        switch(peek())
        {
            case '\"':
                consume();
                return Token("\"", QUOTE_TYPE);
            case ',':
                consume();
                return Token(",", COMMA_TYPE);
            case '!':
                consume();
                return Token("!", EXCL_MARK_TYPE);
            default:
                break;
        }
        if (isDigit(peek()))
        {
            return NUM();
        }
        if (isLetter(peek()))
        {
            return NAME();
        }
        throw std::invalid_argument("Lexing error.");
    }
    return Token("<EOF>", EOF_TYPE);
}

void BasicLexer::WS()
{
    while(peek() == ' ' || peek() == '\t' || peek() == '\n' || peek() == '\r')
    {
        consume();
    }
}

Token BasicLexer::NUM()
{
    std::ostringstream text;
    do
    {
        text << peek();
        consume();
    } while(isDigit(peek()));
    return Token(text.str().c_str(), NUM_TYPE);
}

Token BasicLexer::NAME()
{
    std::ostringstream text;
    do
    {
        text << peek();
        consume();
    } while(isLetter(peek()));
    return Token(text.str().c_str(), NAME_TYPE);
}
