#include "basic_variant.h"

ExpressionNumberValue BasicVariant::toNumber(char const* string, size_t len)
{
    ExpressionNumberValue result = 0;
    for (size_t idx = 0; idx < len; idx++)
    {
        result *= 10;
        result += string[idx] - '0';
    }
    return result;
}
