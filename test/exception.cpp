#include <gtest/gtest.h>

#include "blet/mockc.h"
#include "blet/mutex.h"

using ::testing::_;
using ::testing::Return;

MOCKC_METHOD1(pthread_mutex_lock, int(pthread_mutex_t* __mutex));
MOCKC_METHOD1(pthread_mutex_unlock, int(pthread_mutex_t* __mutex));

GTEST_TEST(mutex, lock) {
    MOCKC_NEW_INSTANCE(pthread_mutex_lock);

    MOCKC_EXPECT_CALL(pthread_mutex_lock, (_))
        .WillOnce(Return(EAGAIN))
        .WillOnce(Return(EINVAL))
        .WillOnce(Return(EDEADLK))
        .WillOnce(Return(EPERM))
        .WillOnce(Return(42));

    MOCKC_GUARD(pthread_mutex_lock);

    EXPECT_THROW(
        {
            try {
                blet::Mutex mutex;
                mutex.lock();
            }
            catch (const blet::Mutex::Exception& e) {
                EXPECT_STREQ(
                    e.what(),
                    "the mutex could not be acquired because the maximum "
                    "number of recursive locks for mutex has been exceeded");
                throw;
            }
        },
        blet::Mutex::Exception);
    EXPECT_THROW(
        {
            try {
                blet::Mutex mutex;
                mutex.lock();
            }
            catch (const blet::Mutex::Exception& e) {
                EXPECT_STREQ(e.what(),
                             "the mutex was created with the protocol "
                             "attribute having the value PTHREAD_PRIO_PROTECT "
                             "and the calling thread's priority is higher than "
                             "the mutex's current priority ceiling");
                throw;
            }
        },
        blet::Mutex::Exception);
    EXPECT_THROW(
        {
            try {
                blet::Mutex mutex;
                mutex.lock();
            }
            catch (const blet::Mutex::Exception& e) {
                EXPECT_STREQ(e.what(),
                             "the current thread already owns the mutex");
                throw;
            }
        },
        blet::Mutex::Exception);
    EXPECT_THROW(
        {
            try {
                blet::Mutex mutex;
                mutex.lock();
            }
            catch (const blet::Mutex::Exception& e) {
                EXPECT_STREQ(e.what(),
                             "the current thread does not own the mutex");
                throw;
            }
        },
        blet::Mutex::Exception);
    EXPECT_THROW(
        {
            try {
                blet::Mutex mutex;
                mutex.lock();
            }
            catch (const blet::Mutex::Exception& e) {
                EXPECT_STREQ(e.what(), "unknown error");
                throw;
            }
        },
        blet::Mutex::Exception);
}

GTEST_TEST(mutex, unlock) {
    MOCKC_NEW_INSTANCE(pthread_mutex_unlock);

    MOCKC_EXPECT_CALL(pthread_mutex_unlock, (_)).WillOnce(Return(EPERM));

    MOCKC_GUARD(pthread_mutex_unlock);

    EXPECT_THROW(
        {
            try {
                blet::Mutex mutex;
                mutex.unlock();
            }
            catch (const blet::Mutex::Exception& e) {
                EXPECT_STREQ(e.what(),
                             "the current thread does not own the mutex");
                throw;
            }
        },
        blet::Mutex::Exception);
}