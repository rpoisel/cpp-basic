#pragma once

#include <stddef.h>
#include <stdint.h>

namespace Lang
{
namespace Basic
{

typedef int64_t ExpressionNumberValue;

enum ExpressionType {
    INVALID,
    STRING,
    NUMBER
};


class BasicVariant
{
    struct ExpressionStringValue
    {
        ExpressionStringValue(char const* base, size_t len) : base(base), len(len) {}

        char const* base;
        size_t len;
    };
    union ExpressionValue {
        ExpressionValue() {}
        ExpressionValue(char const* string, size_t len) : string(string, len) {}
        ExpressionValue(ExpressionNumberValue number) : number(number) {}

        ExpressionStringValue string;
        ExpressionNumberValue number;
    };

public:
    static ExpressionNumberValue toNumber(char const* string, size_t len);

    BasicVariant() : type(INVALID) {}
    BasicVariant(char const* string, size_t len) : type(STRING), value{string, len} {}
    BasicVariant(ExpressionNumberValue number) : type(NUMBER), value{number} {}

    // TODO getType() should be private or removed
    ExpressionType getType() const { return type; }
    ExpressionStringValue asString() const { return value.string; }
    ExpressionNumberValue asNumber() const { return value.number; }

private:
    ExpressionType type;
    ExpressionValue value;
};

}
}
