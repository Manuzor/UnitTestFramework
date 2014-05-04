#pragma once

#define CUT_STRINGIZE_HELPER(x) #x
#define CUT_STRINGIZE(str) CUT_STRINGIZE_HELPER(str)

// Same thing, different name
#define CUT_TOSTRING(str) CUT_STRINGIZE(str)
