#pragma once

#include "basic_facilities.h"

namespace Lang
{
namespace Basic
{

class PosixFacilities : public Facilities
{
public:
    RC print(Token const& stringLiteral);
    RC print(BasicVariant& variant);
    RC print(char const* string, size_t len);
    RC print(ExpressionNumberValue value);
};

}
}
