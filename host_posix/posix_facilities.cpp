#include "posix_facilities.h"

#include <iostream>
#include <string>

namespace Lang
{
namespace Basic
{

RC PosixFacilities::print(Lang::Token const& stringLiteral)
{
    return print(stringLiteral.getText(), stringLiteral.getLen());
}


RC PosixFacilities::print(Lang::Basic::BasicVariant& variant)
{
    if (variant.getType() == Lang::Basic::STRING)
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

RC PosixFacilities::print(Lang::Basic::ExpressionNumberValue value)
{
    std::cout << value << std::flush;
    return RC_OK;
}

}
}
