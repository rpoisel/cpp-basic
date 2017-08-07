#include "basic_lexer.h"

#include <sstream>

Token BasicLexer::nextToken()
{
    while(LA(1) != EOF_CHAR)
    {
        if (isWS(LA(1)))
        {
            WS();
            continue;
        }
        switch(LA(1))
        {
            case ',':
                consume();
                return Token(",", COMMA_TYPE);
            case '\"':
                consume();
                return STRING_LITERAL();
            default:
                break;
        }
        if (isDigit(LA(1)))
        {
            return INTEGER_LITERAL();
        }
        for (auto keyword : KEYWORDS)
        {
            if (foresee(keyword.typeStr))
            {
                return KEYWORD(keyword);
            }
        }
        throw std::invalid_argument("Lexing error.");
    }
    return Token("<EOF>", EOF_TYPE);
}

bool BasicLexer::foresee(std::string const& keyword) const
{
    for (auto idx = 0; idx < keyword.length(); idx++)
    {
        if (LA(idx + 1) != keyword.at(idx))
        {
            return false;
        }
    }
    return !isLetter(LA(keyword.size() + 1));
}

void BasicLexer::WS()
{
    while(LA(1) == ' ' || LA(1) == '\t' || LA(1) == '\n' || LA(1) == '\r')
    {
        consume();
    }
}

Token BasicLexer::INTEGER_LITERAL()
{
    return GROUP(isDigit, INTEGER_LITERAL_TYPE);
}

Token BasicLexer::GROUP(CheckCb cb, TokenType const tokenType)
{
    std::ostringstream text;
    do
    {
        text << LA(1);
        consume();
    } while(cb(LA(1)));
    return Token(text.str().c_str(), tokenType);
}

Token BasicLexer::KEYWORD(TokenType const tokenType)
{
    match(tokenType.typeStr);
    return Token(tokenType.typeStr, tokenType);
}

Token BasicLexer::STRING_LITERAL()
{
    std::ostringstream text;
    while(LA(1) != '\"')
    {
        text << LA(1);
        consume();
    }
    consume();
    return Token(text.str().c_str(), STRING_LITERAL_TYPE);
}
