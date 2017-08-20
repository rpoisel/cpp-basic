#pragma once

#include "token.h"
#include "basic_variant.h"

class BasicFacilities
{
public:
    virtual RC print(Token const& stringLiteral) = 0;
    virtual RC print(BasicVariant& variant) = 0;
    virtual RC print(char const* string, size_t len) = 0;
    virtual RC print(ExpressionNumberValue value) = 0;
};
