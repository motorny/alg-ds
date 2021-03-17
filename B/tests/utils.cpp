#include <gtest/gtest.h>

#include "utils.h"

#include "../memallocator.h"

std::string captureMemDone() {
    testing::internal::CaptureStdout();
    memdone();
    return testing::internal::GetCapturedStdout();
}