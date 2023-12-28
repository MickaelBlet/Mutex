#include <gtest/gtest.h>

#include "blet/mockc.h"
#include "blet/mutex.h"

using ::testing::_;
using ::testing::Return;

MOCKC_METHOD1(pthread_mutex_trylock, int(pthread_mutex_t *__mutex));

GTEST_TEST(mutex, try_lock) {
    MOCKC_NEW_INSTANCE(pthread_mutex_trylock);

    MOCKC_EXPECT_CALL(pthread_mutex_trylock, (_))
        .WillOnce(Return(0))
        .WillOnce(Return(EBUSY));

    MOCKC_GUARD(pthread_mutex_trylock);

    blet::Mutex mutex;
    EXPECT_EQ(mutex.try_lock(), true);
    EXPECT_EQ(mutex.try_lock(), false);
}