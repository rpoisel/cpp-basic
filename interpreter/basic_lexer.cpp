#include "basic_lexer.h"

RC BasicLexer::nextToken(Token& token)
{
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
                consume();
                token = Token(LA(1), 1, NEWLINE_TYPE);
                return RC_OK;
            case '\"':
                consume();
                token = STRING_LITERAL();
                return RC_OK;
            case '+':
                consume();
                token = Token(LA(1), 1, PLUS_TYPE);
                return RC_OK;
            case '-':
                consume();
                token = Token(LA(1), 1, MINUS_TYPE);
                return RC_OK;
            case '*':
                consume();
                token = Token(LA(1), 1, ASTERISK_TYPE);
                return RC_OK;
            case '/':
                consume();
                token = Token(LA(1), 1, DIVIDER_TYPE);
                return RC_OK;
            case '=':
                consume();
                token = Token(LA(1), 1, EQUAL_TYPE);
                return RC_OK;
            default:
                break;
        }
        if (isDigit(*LA(1)))
        {
            token = INTEGER_LITERAL();
            return RC_OK;
        }
        if (isLetter(*LA(1)) && !isLetter(*LA(2)))
        {
            token = Token(LA(1), 1, VAR_TYPE);
            consume();
            return RC_OK;
        }
        if (*LA(1) == '<' && *LA(2) != '=' && *LA(2) != '>')
        {
            token = Token(LA(1), 1, LT_TYPE);
            consume();
            return RC_OK;
        }
        if (*LA(1) == '<' && *LA(2) == '=')
        {
            token = Token(LA(1), 2, LE_TYPE);
            consume();
            consume();
            return RC_OK;
        }
        if (*LA(1) == '>' && *LA(2) != '=')
        {
            token = Token(LA(1), 1, GT_TYPE);
            consume();
            return RC_OK;
        }
        if (*LA(1) == '>' && *LA(2) == '=')
        {
            token = Token(LA(1), 2, GE_TYPE);
            consume();
            consume();
            return RC_OK;
        }
        if (*LA(1) == '<' && *LA(2) == '>')
        {
            token = Token(LA(1), 2, NEQ_TYPE);
            consume();
            consume();
            return RC_OK;
        }
        for (auto keyword : KEYWORDS)
        {
            if (foresee(keyword.typeStr))
            {
                token = KEYWORD(keyword);
                return RC_OK;
            }
        }
        token = Token(LA(1), 1, NA_TYPE);
        consume();
        return RC_OK;
    }
    token = Token(LA(1), EOF_TYPE);
    return RC_OK;
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
    Token token(LA(1), tokenType);
    do
    {
        token.setLen(token.getLen() + 1);
        consume();
    } while(cb(*LA(1)));
    return token;
}

Token BasicLexer::KEYWORD(KeywordTokenType const& tokenType)
{
    Token token(LA(1), tokenType.typeId);

    size_t len;
    match(tokenType.typeStr, len);
    token.setLen(len);

    return token;
}

Token BasicLexer::STRING_LITERAL()
{
    Token token(LA(1), STRING_LITERAL_TYPE);
    while(*LA(1) != '\"')
    {
        token.setLen(token.getLen() + 1);
        consume();
    }
    consume();
    return token;
}
