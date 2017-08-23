#pragma once

#include "basic_lexer.h"
#include "basic_interpreter_fwd.h"

class BasicCommandRegistry
{
public:
    RC handleStatement(BasicInterpreter* const interpreter) const;
};

extern const BasicCommandRegistry basicCommandRegistry;
