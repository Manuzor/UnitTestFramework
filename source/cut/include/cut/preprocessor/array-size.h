#pragma once

/// compile-time size of a static array
#define CUT_ARRAY_SIZE(arr) sizeof(ArraySizeHelper(arr))

namespace
{
    template<typename T, size_t N>
    char (&ArraySizeHelper(const T (&)[N]))[N];
}
