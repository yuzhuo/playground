
#include "thread_pool.h"

void Thread::start()
{
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    
    int detachstate = joinable_ ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED;
    pthread_attr_setdetachstate(&attr, detachstate);
    pthread_create(&tid_, &attr, &ThreadRunner, this);

    pthread_attr_destroy(&attr);
}


void WorkerThread::join()
{
    pthread_join(tid_, NULL);
}


void ThreadPool::start_all_workers()
{
    for (int i = 0; i < pool_size_; ++i) {
        pool_[i]->start();
    }
}
