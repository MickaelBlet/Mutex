/**
 * mutex.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2024 BLET Mickaël.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BLET_MUTEX_H_
#define BLET_MUTEX_H_

#include <errno.h>
#include <pthread.h>

#include <exception>

#define BLET_MUTEX_EXCEPTION_EINVAL_                                         \
    "the mutex was created with the protocol attribute having the value "    \
    "PTHREAD_PRIO_PROTECT and the calling thread's priority is higher than " \
    "the mutex's current priority ceiling"
#define BLET_MUTEX_EXCEPTION_EAGAIN_                                           \
    "the mutex could not be acquired because the maximum number of recursive " \
    "locks for mutex has been exceeded"
#define BLET_MUTEX_EXCEPTION_EDEADLK_ \
    "the current thread already owns the mutex"
#define BLET_MUTEX_EXCEPTION_EPERM_ "the current thread does not own the mutex"

namespace blet {

class Mutex {
  public:
    class Exception : public std::exception {
      public:
        Exception(const Mutex& mutex, int retValue) :
            std::exception(),
            mutex_(mutex) {
            switch (retValue) {
                case EINVAL:
                    what_ = BLET_MUTEX_EXCEPTION_EINVAL_;
                    break;
                case EAGAIN:
                    what_ = BLET_MUTEX_EXCEPTION_EAGAIN_;
                    break;
                case EDEADLK:
                    what_ = BLET_MUTEX_EXCEPTION_EDEADLK_;
                    break;
                case EPERM:
                    what_ = BLET_MUTEX_EXCEPTION_EPERM_;
                    break;
                default:
                    what_ = "unknown error";
                    break;
            }
        }
        virtual ~Exception() throw() {}
        const char* what() const throw() {
            return what_;
        }

      protected:
        const char* what_;
        const Mutex& mutex_;
    };

    /**
     * @brief The mutex class is a synchronization primitive that can be used to
     * protect shared data from being simultaneously accessed by multiple
     * threads.
     *
     * mutex offers exclusive, non-recursive ownership semantics:
     *
     * A calling thread owns a mutex from the time that it successfully calls
     * either lock or try_lock until it calls unlock. When a thread owns a
     * mutex, all other threads will block (for calls to lock) or receive a
     * false return value (for try_lock) if they attempt to claim ownership of
     * the mutex. A calling thread must not own the mutex prior to calling lock
     * or try_lock. The behavior of a program is undefined if a mutex is
     * destroyed while still owned by any threads, or a thread terminates while
     * owning a mutex.
     *
     * @param pAttr The attributes of mutex.
     */
    Mutex(const pthread_mutexattr_t* pAttr = NULL) {
        ::pthread_mutex_init(&mutex_, pAttr);
    }

    /**
     * @brief Destroy the Mutex object.
     */
    ~Mutex() {
        ::pthread_mutex_destroy(&mutex_);
    }

    /**
     * @brief Locks the mutex.
     *
     * If another thread has already locked the mutex, a call to lock will block
     * execution until the lock is acquired. If lock is called by a thread that
     * already owns the mutex, the behavior is undefined: for example, the
     * program may deadlock. An implementation that can detect the invalid usage
     * is encouraged to throw a Exception with error condition
     * resource_deadlock_would_occur instead of deadlocking.
     */
    void lock() {
        int retLock = ::pthread_mutex_lock(&mutex_);
        if (retLock) {
            throw Exception(*this, retLock);
        }
    }

    /**
     * @brief Tries to lock the mutex.
     * Returns immediately. On successful lock acquisition returns true,
     * otherwise returns false.
     *
     * This function is allowed to fail spuriously and return false even if the
     * mutex is not currently locked by any other thread.
     *
     * If try_lock is called by a thread that already owns the mutex, the
     * behavior is undefined.
     */
    bool try_lock() {
        int retLock = ::pthread_mutex_trylock(&mutex_);
        return !retLock;
    }

    /**
     * @brief Unlocks the mutex.
     *
     * The mutex must be locked by the current thread of execution, otherwise,
     * the behavior is undefined.
     *
     * This operation synchronizes-with (as defined in std::memory_order) any
     * subsequent lock operation that obtains ownership of the same mutex.
     */
    void unlock() {
        int retUnlock = ::pthread_mutex_unlock(&mutex_);
        if (retUnlock) {
            throw Exception(*this, retUnlock);
        }
    }

    /**
     * @return pthread_mutex_t& Reference of real mutex structrure.
     */
    pthread_mutex_t& native_handle() {
        return mutex_;
    }

  protected:
    pthread_mutex_t mutex_;

  private:
    Mutex(const Mutex&) {}
    Mutex& operator=(const Mutex&) {
        return *this;
    }
};

template<class Mutex>
class LockGuard {
  public:
    LockGuard(Mutex& mutex) :
        mutex_(mutex) {
        mutex_.lock();
    }
    ~LockGuard() {
        mutex_.unlock();
    }

  protected:
    Mutex& mutex_;

  private:
    LockGuard(const LockGuard&) {}
    LockGuard& operator=(const LockGuard&) {
        return *this;
    }
};

} // namespace blet

#undef BLET_MUTEX_EXCEPTION_EINVAL_
#undef BLET_MUTEX_EXCEPTION_EAGAIN_
#undef BLET_MUTEX_EXCEPTION_EDEADLK_
#undef BLET_MUTEX_EXCEPTION_EPERM_

#endif // #ifndef BLET_MUTEX_H_