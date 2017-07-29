
#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread
{
public:
    Thread(bool joinable) : joinable_(joinable) {}
    virtual ~Thread() {}

    void start()
    {
        pthread_attr_t attr;

        pthread_attr_init(&attr);
        
        int detachstate = joinable_ ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED;
        pthread_attr_setdetachstate(&attr, detachstate);
        pthread_create(&tid_, &attr, &Thread::thread_runner, this);

        pthread_attr_destroy(&attr);
    }

    pthread_t thread_id()
    {
        return tid_;
    }

public:
    Thread(const Thread& rhs) = delete;
    Thread& operator=(const Thread& rhs) = delete;

protected:
    virtual void run() = 0;

    static void* thread_runner(void *args)
    {
        Thread *t = static_cast<Thread*>(args);
        t->run();
        return nullptr;
    }

protected:
    bool joinable_;
    pthread_t tid_;
};

class JoinableThread : public Thread
{
public:
    JoinableThread()
        : Thread(true)
    {  }

    void join()
    {
        pthread_join(tid_, NULL);
    }
};

class NonjoinableThread : public Thread
{
public:
    NonjoinableThread()
        : Thread(false)
    {  }
};

#endif /* __THREAD_H__ */
