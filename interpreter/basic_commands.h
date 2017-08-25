#pragma once

#include "basic_lexer.h"
#include "basic_interpreter_fwd.h"

class BasicCommand
{
public:
    constexpr BasicCommand(TokenIdType const& tokenId) : tokenId(tokenId) {}
    virtual RC execute(BasicInterpreter* const interpreter) const = 0;
    constexpr TokenIdType const& getTokenId() const { return tokenId; }
private:
    TokenIdType const& tokenId;
};

class BasicCommandRegistry
{
public:
    RC handleStatement(BasicInterpreter* const interpreter) const;
};

extern const BasicCommandRegistry basicCommandRegistry;
