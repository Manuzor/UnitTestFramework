#pragma once

#define CUT_CONCAT_HELPER_2(x, y) x ## y
#define CUT_CONCAT_HELPER(x, y) CUT_CONCAT_HELPER_2(x, y)
#define CUT_CONCAT(x, y) CUT_CONCAT_HELPER(x, y)
