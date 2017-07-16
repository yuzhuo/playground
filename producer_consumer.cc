

#include "mutex.h"
#include "thread_pool.h"
#include <stdio.h>
#include <unistd.h>

MutexLock mutex;
Condition empty(mutex);
Condition full(mutex);

const int kBufSize = 10;
typedef struct buffer {
    char buf[kBufSize];
    int nextin;
    int nextout;
    int occupied;
    int n_producer;
} buffer_t;

void buffer_init(buffer_t *buffer)
{
    buffer->nextin = buffer->nextout = 0;
    buffer->occupied = 0;
    buffer->n_producer = 0;
}

class Producer : public Thread
{
public:
    Producer(buffer_t &buf)
        : Thread(true)
        , buffer_(buf)
        , ch_('a')
        , id_(Producer::id_generator_)
    {
        MutexLockGuard mlg(mutex);
        ++buffer_.n_producer;
        Producer::id_generator_ += 1;
    }

    virtual void run()
    {
        while (true) {
            MutexLockGuard mlg(mutex);

            while (buffer_.occupied >= kBufSize) {
                printf("waiting on full\n");
                full.wait();
            }

            printf("producer %d produces [%c]\n", id_, ch_);
            buffer_.buf[buffer_.nextin] = ch_;
            buffer_.nextin = (buffer_.nextin + 1) % kBufSize;
            ++buffer_.occupied;
            ++ch_;

            empty.notify_all();
            if ('h' == ch_) {
                --buffer_.n_producer;
                printf("producer %d exits. producer num: %d\n", id_, buffer_.n_producer);
                pthread_exit(NULL);
            }
        }
    }

    void join()
    {
        pthread_join(tid_, NULL);
    }

private:
    static int id_generator_;

    buffer_t& buffer_;
    char ch_;
    int id_;
};
int Producer::id_generator_ = 1;

class Consumer : public Thread
{
public:
    Consumer(buffer_t &buf)
        : Thread(true)
        , buffer_(buf)
        , id_(Consumer::id_generator_)
    {
        Consumer::id_generator_ += 1;
    }

    virtual void run()
    {
        while (true) {
            MutexLockGuard mlg(mutex);

            while (0 == buffer_.occupied) {
                if (0 == buffer_.n_producer) {
                    printf(" *** consumer %d exits\n", id_);
                    pthread_exit(NULL);
                }

                printf(" *** waiting on empty\n");
                empty.wait();
            }

            char ch = buffer_.buf[buffer_.nextout];
            printf(" *** consumer %d consumes [%c]\n", id_, ch);
            buffer_.nextout = (buffer_.nextout + 1) % kBufSize;
            --buffer_.occupied;

            full.notify_all();
        }
    }

    void join()
    {
        pthread_join(tid_, NULL);
    }

private:
    static int id_generator_;

    buffer_t& buffer_;
    int id_;
};
int Consumer::id_generator_ = 1;

int main()
{
    buffer_t buffer;
    buffer_init(&buffer);
    Producer p1(buffer);
    Producer p2(buffer);
    Producer p3(buffer);
    Producer p4(buffer);
    p1.start();
    p2.start();
    p3.start();
    p4.start();

    sleep(1);

    Consumer c1(buffer);
    Consumer c2(buffer);
    c1.start();
    c2.start();

    cout << "main before join" << endl;
    p1.join();
    p2.join();
    p3.join();
    c1.join();
    c2.join();
    cout << "main after join" << endl;

    return 0;
}


