
#ifndef __MUTEX_H__
#define __MUTEX_H__

//#include <stdio.h>
#include "pthread.h"

class Condition;

class MutexLock
{
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex_, NULL);
        //printf("MutexLock()\n");
    }

    MutexLock(const MutexLock&) = delete;
    MutexLock& operator=(const MutexLock&) = delete;

    ~MutexLock()
    {
        pthread_mutex_destroy(&mutex_);
        //printf("~MutexLock()\n");
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);
        //printf("MutexLock::lock()\n");
    }

    void unlock()
    {
        int ret = pthread_mutex_unlock(&mutex_);
        //printf("MutexLock::unlock()\n");
        //printf("unlock ret: %d\n", ret);
    }
    
private:
    friend class Condition;
    pthread_mutex_t* get_pthread_mutex()
    {
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock& mutex)
        : mutex_(mutex)
    {
        //printf("MutexLockGuard()\n");
        mutex_.lock();
    }

    MutexLockGuard(const MutexLockGuard&) = delete;
    MutexLockGuard& operator=(const MutexLockGuard&) = delete;

    ~MutexLockGuard()
    {
        //printf("~MutexLockGuard()\n");
        mutex_.unlock();
    }

private:
    MutexLock &mutex_;
};
#define MutexLockGuard(x) no_variable_specified_err

class Condition
{
public:
    Condition()
    {
        pthread_cond_init(&cond_, NULL);
    }

    Condition(const Condition&) = delete;
    Condition& operator=(const Condition&) = delete;

    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }

    void wait(MutexLock& mutex)
    {
        pthread_cond_wait(&cond_, mutex.get_pthread_mutex());
    }

    void notify()
    {
        pthread_cond_signal(&cond_);
    }

    void notify_all()
    {
        pthread_cond_broadcast(&cond_);
    }

private:
    pthread_cond_t cond_;
};

#endif /* __MUTEX_H__ */
