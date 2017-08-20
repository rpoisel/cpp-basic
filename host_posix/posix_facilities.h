#pragma once

#include "basic_facilities.h"

class PosixFacilities : public BasicFacilities
{
public:
    RC print(Token const& stringLiteral);
    RC print(BasicVariant& variant);
    RC print(char const* string, size_t len);
    RC print(ExpressionNumberValue value);
};

