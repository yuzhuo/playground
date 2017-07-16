
#include <stdio.h>
#include "pthread.h"
#include "mutex.h"

int val = 0;
const int kTimes = 1000 * 1000;
MutexLock mutex;

void *func(void *arg)
{
    for (int i = 0; i < kTimes; ++i) {
        MutexLockGuard sm(mutex);
        int tmp = val;
        tmp += 100 * 100;
        tmp -= 100 * 100;
        val = tmp + 1;
    }
}

int main()
{
    printf("%d\n", val);

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, func, NULL);

    for (int i = 0; i < kTimes; ++i) {
        MutexLockGuard sm(mutex);
        int tmp = val;
        tmp += 100 * 100;
        tmp -= 100 * 100;
        val = tmp + 1;
    }

    printf("before join\n");
    pthread_join(tid, NULL);
    printf("after join\n");

    pthread_attr_destroy(&attr);

    printf("%d\n", val);

    return 0;
}
