#pragma once

#include "basic_facilities.h"

class ArduinoFacilities : public BasicFacilities
{
public:
    ArduinoFacilities();
    RC print(Token const& stringLiteral);
    RC print(BasicVariant& variant);
    RC print(char const* string, size_t len);
    RC print(ExpressionNumberValue value);
};


