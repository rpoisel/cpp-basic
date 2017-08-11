#pragma once

#include <cstdint>

typedef uint8_t const RC;

constexpr RC RC_OK = 0x00;
constexpr RC RC_ERROR = 0x80;

constexpr bool RC_SUCCEEDED(RC x) { return !(x & RC_ERROR); }
constexpr bool RC_FAILED(RC x) { return !RC_SUCCEEDED(x); }
