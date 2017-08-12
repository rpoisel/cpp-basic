#include "basic_parser.h"

BasicParser::BasicParser(BasicLexer& lexer) : lexer(lexer), p(0)
{
    for (size_t idx = 0; idx < K; idx++)
    {
        consume();
    }
}

RC BasicParser::parse()
{
    RC rc;
    do
    {
        rc = line();
    } while (RC_SUCCEEDED(rc) && rc != RC_FINISH);
    return rc;
}

void BasicParser::consume()
{
    lexer.nextToken(lookahead[p]);
    p = (p + 1) % K;
}

RC BasicParser::match(TokenType const& tokenType)
{
    if (LA(1).getType() == tokenType)
    {
        consume();
        return RC_OK;
    }
    return RC_ERROR;
}

RC BasicParser::line()
{
    if (LA(1).getType() == EOF_TYPE)
    {
        return RC_FINISH;
    }

    RC rc;
    if (LA(1).getType() == INTEGER_LITERAL_TYPE)
    {
        // ignore line number for the moment
        // TODO; add line number to jumplist
        rc = match(INTEGER_LITERAL_TYPE);
        if (RC_FAILED(rc))
        {
            return rc;
        }
    }
    rc = statement();
    if (RC_FAILED(rc))
    {
        return rc;
    }
    rc = match(NEWLINE_TYPE);
    if (RC_FAILED(rc))
    {
        return rc;
    }
    return RC_OK;
}

RC BasicParser::statement()
{
    if (LA(1).getType() == KEYWORDS[PRINT_IDX])
    {
        consume();
        if (LA(1).getType() == STRING_LITERAL_TYPE)
        {
            consume();
            return RC_OK;
        }
        return RC_ERROR;
    }
    else if (LA(1).getType() == KEYWORDS[GOTO_IDX])
    {
        consume();
        return match(INTEGER_LITERAL_TYPE);
    }
    return RC_ERROR;
}

