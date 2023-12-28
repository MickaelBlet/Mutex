#include <gtest/gtest.h>

#include "blet/mockc.h"
#include "blet/mutex.h"

using ::testing::_;
using ::testing::Return;

MOCKC_METHOD1(pthread_mutex_lock, int(pthread_mutex_t* __mutex));

GTEST_TEST(mutex, lock) {
    MOCKC_NEW_INSTANCE(pthread_mutex_lock);

    MOCKC_EXPECT_CALL(pthread_mutex_lock, (_)).WillOnce(Return(0));

    MOCKC_GUARD(pthread_mutex_lock);

    EXPECT_NO_THROW({
        blet::Mutex mutex;
        mutex.lock();
    });
}