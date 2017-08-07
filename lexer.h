#pragma once

#include <sstream>

typedef size_t TokenIdType;
typedef struct _TokenType TokenType;
struct _TokenType
{
    TokenType& operator=(TokenType const& other);
    TokenIdType typeId;
    char const* typeStr;
};

constexpr TokenType const NA_TYPE { 0, "n/a" };
constexpr TokenType const EOF_TYPE { 1, "EOF" };

constexpr char const EOF_CHAR = -1;

class Token
{
public:
    Token(char const* te, TokenType const ty) : text(te), type(ty) {}
    Token(Token const& other);

    Token& operator=(Token&& other);

    std::string text;
    TokenType type;
};
std::ostream & operator<<(std::ostream &os, Token const &token);

template <int k>
class Lexer
{
public:
    Lexer(char const* input);
    virtual ~Lexer() {}

    virtual Token nextToken() = 0;

    void match(char const x);
    void match(std::string const& str);
    char LA(size_t i) const { return lookahead[(p + i - 1) % k]; }
    void consume();
private:

    char const* const input;
    char const* cur;
    char lookahead[k];
    size_t p;
};

template <int k>
Lexer<k>::Lexer(char const* input) : input(input), cur(input), p(0)
{
    for(auto i = 0; i < sizeof(lookahead) / sizeof(lookahead[0]); i++)
    {
        consume();
    }
}

template <int k>
void Lexer<k>::consume()
{
    if (!*cur)
    {
        lookahead[p] = EOF_CHAR;
    }
    else
    {
        lookahead[p] = *cur;
        cur++;
    }
    p = (p + 1) % k;
}

template <int k>
void Lexer<k>::match(char const x)
{
    if (LA(1) == x)
    {
        consume();
        return;
    }
    std::ostringstream errorMsg;
    errorMsg << "expecting " << x << ", found " << LA(1);
    throw std::invalid_argument(errorMsg.str());
}

template <int k>
void Lexer<k>::match(std::string const& str)
{
    for (auto idx = 0; idx < str.size(); idx++)
    {
        match(str.at(idx));
    }
}
