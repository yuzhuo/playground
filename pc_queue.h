
#ifndef __PC_QUEUE_H__
#define __PC_QUEUE_H__

#include <queue>
#include <stdio.h>

#include "mutex.h"

template <typename Elem>
class ProducerConsumerQueue
{
public:
    ProducerConsumerQueue(int c)
    {
        n_producer_ = 0;
        capacity_ = c;
    }

    ProducerConsumerQueue(const ProducerConsumerQueue&) = delete;
    ProducerConsumerQueue& operator=(const ProducerConsumerQueue&) = delete;

    // only can be called by consumer thread
    int consume(Elem& elem)
    {
        MutexLockGuard mlg(mutex_);

        while (0 == buf_.size()) {
            if (!has_work_todo()) {
                printf(" *** no work to do\n");
                return -1;
            }
            printf(" *** wait to consume. producers: %d\n", n_producer_);
            empty_.wait(mutex_);
        }

        elem = buf_.front();
        buf_.pop();

        printf(" *** consumer consumes an element\n");
        full_.notify_all();
        return 0;
    }

    // only can be called by producer thread
    void produce(Elem& elem)
    {
        MutexLockGuard mlg(mutex_);

        while (capacity_ > 0 && buf_.size() >= capacity_) {
            full_.wait(mutex_);
        }

        buf_.push(elem);

        printf("produces an element\n");
        empty_.notify_all();
    }

    void add_a_producer()
    {
        ++n_producer_;
    }

    void remove_a_producer()
    {
        --n_producer_;
        if (0 == n_producer_) {
            printf("notify all consumers.\n");
            empty_.notify_all();
        }
    }

    // determine whether consumer thread should exit
    // when there is no work to consume and no producer, the consumer should exit
    bool has_work_todo()
    {
        return 0 != buf_.size() || 0 != n_producer_;
    }

private:
    int n_producer_;
    int capacity_;
    std::queue<Elem> buf_;
    MutexLock mutex_;
    Condition empty_;
    Condition full_;
};


#endif /* __PC_QUEUE_H__ */
