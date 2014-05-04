#pragma once

#if !defined(_WIN32) && !defined(_WIN64)
#error "Current compiler is not supported!"
#endif

#include "cut/common.h"
#include "cut/unit-test-manager.h"
#include "cut/unit-test-group.h"
#include "cut/unit-test.h"
#include "cut/assert.h"
