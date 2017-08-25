#include "basic_lexer.h"

Token BasicLexer::nextToken(RC& rc)
{
    Token result;
    while(*LA(1))
    {
        if (isWS(*LA(1)))
        {
            WS();
            continue;
        }
        switch(*LA(1))
        {
            case '\n':
                result = Token(LA(1), 1, NEWLINE_TYPE);
                consume();
                rc = RC_OK;
                return result;
            case '\"':
                consume();
                result = STRING_LITERAL();
                consume();
                rc = RC_OK;
                return result;
            case '+':
                result = Token(LA(1), 1, PLUS_TYPE);
                consume();
                rc = RC_OK;
                return result;
            case '-':
                result = Token(LA(1), 1, MINUS_TYPE);
                consume();
                rc = RC_OK;
                return result;
            case '*':
                result = Token(LA(1), 1, ASTERISK_TYPE);
                consume();
                rc = RC_OK;
                return result;
            case '/':
                result = Token(LA(1), 1, DIVIDER_TYPE);
                consume();
                rc = RC_OK;
                return result;
            case '=':
                result = Token(LA(1), 1, EQUAL_TYPE);
                consume();
                rc = RC_OK;
                return result;
            default:
                break;
        }
        if (isDigit(*LA(1)))
        {
            rc = RC_OK;
            return INTEGER_LITERAL();
        }
        if (isLetter(*LA(1)) && !isLetter(*LA(2)))
        {
            result = Token(LA(1), 1, VAR_TYPE);
            consume();
            rc = RC_OK;
            return result;
        }
        if (*LA(1) == '<' && *LA(2) != '=' && *LA(2) != '>')
        {
            result = Token(LA(1), 1, LT_TYPE);
            consume();
            rc = RC_OK;
            return result;
        }
        if (*LA(1) == '<' && *LA(2) == '=')
        {
            result = Token(LA(1), 2, LE_TYPE);
            consume();
            consume();
            rc = RC_OK;
            return result;
        }
        if (*LA(1) == '>' && *LA(2) != '=')
        {
            result = Token(LA(1), 1, GT_TYPE);
            consume();
            rc = RC_OK;
            return result;
        }
        if (*LA(1) == '>' && *LA(2) == '=')
        {
            result = Token(LA(1), 2, GE_TYPE);
            consume();
            consume();
            rc = RC_OK;
            return result;
        }
        if (*LA(1) == '<' && *LA(2) == '>')
        {
            result = Token(LA(1), 2, NEQ_TYPE);
            consume();
            consume();
            rc = RC_OK;
            return result;
        }
        for (auto keyword : KEYWORDS)
        {
            if (foresee(keyword.typeStr))
            {
                rc = RC_OK;
                return KEYWORD(keyword);
            }
        }
        result = Token(LA(1), 1, NA_TYPE);
        consume();
        rc = RC_OK;
        return result;
    }
    rc = RC_OK;
    return Token(LA(1), EOF_TYPE);
}

bool BasicLexer::foresee(char const* keyword) const
{
    size_t idx;
    for (idx = 0; keyword[idx]; idx++)
    {
        if (*LA(idx + 1) != keyword[idx])
        {
            return false;
        }
    }
    return !isLetter(*LA(idx + 1));
}

void BasicLexer::WS()
{
    while(*LA(1) == ' ' || *LA(1) == '\t' || *LA(1) == '\n' || *LA(1) == '\r')
    {
        consume();
    }
}

Token BasicLexer::INTEGER_LITERAL()
{
    return GROUP(isDigit, INTEGER_LITERAL_TYPE);
}

Token BasicLexer::GROUP(CheckCb cb, TokenIdType const& tokenType)
{
    char const* begin = LA(1);
    size_t len = 0;
    do
    {
        len++;
        consume();
    } while(cb(*LA(1)));
    return Token(begin, len, tokenType);
}

Token BasicLexer::KEYWORD(KeywordTokenType const& tokenType)
{
    char const* begin = LA(1);
    size_t len;
    match(tokenType.typeStr, len);

    return Token(begin, len, tokenType.typeId);
}

Token BasicLexer::STRING_LITERAL()
{
    char const* begin = LA(1);
    size_t len = 0;
    while(*LA(1) != '\"')
    {
        len++;
        consume();
    }
    return Token(begin, len, STRING_LITERAL_TYPE);
}
