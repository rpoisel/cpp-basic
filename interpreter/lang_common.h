#pragma once

#include <stdint.h>

namespace Lang
{

typedef uint8_t RC;

constexpr RC const RC_OK = 0x00;
constexpr RC const RC_FINISH = 0x01;
constexpr RC const RC_CONTINUE = 0x02;
constexpr RC const RC_ERROR = 0x80;
constexpr RC const RC_NOTIMPL = 0x81;

constexpr bool RC_SUCCEEDED(RC x)
{
  return !(x & RC_ERROR);
}
constexpr bool RC_FAILED(RC x)
{
  return !RC_SUCCEEDED(x);
}

}
