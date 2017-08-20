#include "posix_facilities.h"

#include <iostream>
#include <string>

RC PosixFacilities::print(Token const& stringLiteral)
{
    return print(stringLiteral.getText(), stringLiteral.getLen());
}


RC PosixFacilities::print(BasicVariant& variant)
{
    if (variant.getType() == STRING)
    {
        return print(variant.asString().base, variant.asString().len);
    }
    return print(variant.asNumber());
}

RC PosixFacilities::print(char const* string, size_t len)
{
    std::string str(string, string + len);
    std::cout << str << std::flush;
    return RC_OK;
}

RC PosixFacilities::print(ExpressionNumberValue value)
{
    std::cout << value << std::flush;
    return RC_OK;
}
