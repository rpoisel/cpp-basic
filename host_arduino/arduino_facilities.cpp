#include "arduino_facilities.h"

#include <Arduino.h>

#include <stdint.h>

namespace Lang
{
namespace Basic
{

ArduinoFacilities::ArduinoFacilities()
{
    Serial.begin(9600);
}

RC ArduinoFacilities::print(Token const& stringLiteral)
{
    return print(stringLiteral.getText(), stringLiteral.getLen());
}

RC ArduinoFacilities::print(BasicVariant& variant)
{
    if (variant.getType() == STRING)
    {
        return print(variant.asString().base, variant.asString().len);
    }
    return print(variant.asNumber());
}

RC ArduinoFacilities::print(char const* string, size_t len)
{
    Serial.print(string); // TODO: consider length
    Serial.flush();
    return RC_OK;
}

RC ArduinoFacilities::print(ExpressionNumberValue value)
{
    Serial.print(static_cast<long int>(value));
    Serial.flush();
    return RC_OK;
}

}
}
