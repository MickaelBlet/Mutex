#ifndef _BLET_MUTEX_H_
#define _BLET_MUTEX_H_

#include <errno.h>
#include <pthread.h>

#include <exception>

#define _BLET_MUTEX_EXCEPTION_EINVAL                                         \
    "the mutex was created with the protocol attribute having the value "    \
    "PTHREAD_PRIO_PROTECT and the calling thread's priority is higher than " \
    "the mutex's current priority ceiling"
#define _BLET_MUTEX_EXCEPTION_EAGAIN                                           \
    "the mutex could not be acquired because the maximum number of recursive " \
    "locks for mutex has been exceeded"
#define _BLET_MUTEX_EXCEPTION_EDEADLK \
    "the current thread already owns the mutex"
#define _BLET_MUTEX_EXCEPTION_EPERM "the current thread does not own the mutex"

namespace blet {

class Mutex {
  public:
    class Exception : public std::exception {
      public:
        Exception(const Mutex& mutex, int retValue) :
            std::exception(),
            _mutex(mutex) {
            switch (retValue) {
                case EINVAL:
                    _what = _BLET_MUTEX_EXCEPTION_EINVAL;
                    break;
                case EAGAIN:
                    _what = _BLET_MUTEX_EXCEPTION_EAGAIN;
                    break;
                case EDEADLK:
                    _what = _BLET_MUTEX_EXCEPTION_EDEADLK;
                    break;
                case EPERM:
                    _what = _BLET_MUTEX_EXCEPTION_EPERM;
                    break;
                default:
                    _what = "unknown error";
                    break;
            }
        }
        virtual ~Exception() throw() {}
        const char* what() const throw() {
            return _what;
        }

      protected:
        const char* _what;
        const Mutex& _mutex;
    };

    /**
     * @brief The mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.
     *
     * mutex offers exclusive, non-recursive ownership semantics:
     *
     * A calling thread owns a mutex from the time that it successfully calls either lock or try_lock until it calls unlock.
     * When a thread owns a mutex, all other threads will block (for calls to lock) or receive a false return value (for try_lock) if they attempt to claim ownership of the mutex.
     * A calling thread must not own the mutex prior to calling lock or try_lock.
     * The behavior of a program is undefined if a mutex is destroyed while still owned by any threads, or a thread terminates while owning a mutex.
     *
     * @param pAttr The attributes of mutex.
     */
    Mutex(const pthread_mutexattr_t* pAttr = NULL) {
        ::pthread_mutex_init(&_mutex, pAttr);
    }

    /**
     * @brief Destroy the Mutex object.
     */
    ~Mutex() {
        ::pthread_mutex_destroy(&_mutex);
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
        int retLock = ::pthread_mutex_lock(&_mutex);
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
        int retLock = ::pthread_mutex_trylock(&_mutex);
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
        int retUnlock = ::pthread_mutex_unlock(&_mutex);
        if (retUnlock) {
            throw Exception(*this, retUnlock);
        }
    }

    /**
     * @return pthread_mutex_t& Reference of real mutex structrure.
     */
    pthread_mutex_t& native_handle() {
        return _mutex;
    }

  protected:
    pthread_mutex_t _mutex;

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
        _mutex(mutex) {
        _mutex.lock();
    }
    ~LockGuard() {
        _mutex.unlock();
    }

  protected:
    Mutex& _mutex;

  private:
    LockGuard(const LockGuard&) {}
    LockGuard& operator=(const LockGuard&) {
        return *this;
    }
};

} // namespace blet

#undef _BLET_MUTEX_EXCEPTION_EINVAL
#undef _BLET_MUTEX_EXCEPTION_EAGAIN
#undef _BLET_MUTEX_EXCEPTION_EDEADLK
#undef _BLET_MUTEX_EXCEPTION_EPERM

#endif // #ifndef _BLET_MUTEX_H_