# Mutex

std::mutex and std::lock_guard for C++ 98 on one header only file.

[mutex.h](include/blet/mutex.h)

## Quickstart

```cpp
#include <unistd.h>

#include <iostream>

#include "blet/mutex.h"

static void* routine(void* e) {
    blet::Mutex* pMutex = reinterpret_cast<blet::Mutex*>(e);
    {
        blet::LockGuard<blet::Mutex> lockguard(*pMutex);
        std::cout << "Hello thread" << std::endl;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    pthread_t tid;
    blet::Mutex mutex;

    mutex.lock();
    pthread_create(&tid, NULL, &routine, &mutex);
    sleep(1);
    mutex.unlock();
    sleep(0);
    {
        blet::LockGuard<blet::Mutex> lockguard(mutex);
        std::cout << "Hello main" << std::endl;
    }
    pthread_join(tid, NULL);

    return 0;
}

// ouput:
// Hello thread
// Hello main
```