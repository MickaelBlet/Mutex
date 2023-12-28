#include <gtest/gtest.h>

#include "blet/mockc.h"
#include "blet/mutex.h"

GTEST_TEST(lockguard, contruct) {
    EXPECT_NO_THROW({
        blet::Mutex mutex;
        blet::LockGuard<blet::Mutex> lockguard(mutex);
    });
}