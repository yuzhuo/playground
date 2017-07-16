
#include <stdio.h>
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
    MutexLock(const MutexLock&);
    MutexLock& operator=(const MutexLock&);

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

    ~MutexLockGuard()
    {
        //printf("~MutexLockGuard()\n");
        mutex_.unlock();
    }

private:
    MutexLockGuard(const MutexLockGuard&);
    MutexLockGuard& operator=(const MutexLockGuard&);

    MutexLock &mutex_;
};
#define MutexLockGuard(x) no_variable_specified_err

class Condition
{
public:
    Condition(MutexLock &mutex)
        : mutex_(mutex)
    {
        pthread_cond_init(&cond_, NULL);
    }

    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }

    void wait()
    {
        pthread_cond_wait(&cond_, mutex_.get_pthread_mutex());
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
    Condition(const Condition&);
    Condition& operator=(const Condition&);

private:
    pthread_cond_t cond_;
    MutexLock& mutex_;
};

