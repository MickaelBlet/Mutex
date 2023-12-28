#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "blet/mockc.h"
#include "blet/mutex.h"

GTEST_TEST(mutex, native_handle) {
    EXPECT_NO_THROW(
        {
            blet::Mutex mutex;
            mutex.native_handle();
        }
    );
}