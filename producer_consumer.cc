

#include "mutex.h"
#include "thread_pool.h"
#include <stdio.h>

const int kBufSize = 10;
typedef struct buffer {
    char buf[kBufSize];
    int nextin;
    int nextout;
    int occupied;

    MutexLock mutex;
    Condition less;
    Condition more;
} buffer_t;

void buffer_init(buffer_t *buffer)
{
    buffer->nextin = buffer->nextout = 0;
    buffer->occupied = 0;
}

class Producer : public Thread
{
public:
    Producer(buffer_t &buf)
        : buffer_(buf)
    { }

    virtual void run()
    {
        MutexLockGuard mlg(buffer_.mutex);

        while (buffer_.occupied >= kBufSize)
            buffer_.more.wait()
    }

private:
    buffer_t buffer_;
};

class Consumer : public Thread
{
public:
    Consumer(buffer_t &buf)
        : buffer_(buf)
    { }

    virtual void run()
    {

    }

private:
    buffer_t buffer_;
};



