
#ifndef __PC_QUEUE_H__
#define __PC_QUEUE_H__

#include "log.h"

#include <queue>
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
                LOG_INFO(" *** no work to do");

                return -1;
            }

            LOG_INFO(" *** wait to consume. producers: %", n_producer_);

            empty_.wait(mutex_);
        }

        elem = buf_.front();
        buf_.pop();

        LOG_INFO(" *** consumer consumes an element");

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

        LOG_INFO("produces an element");
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
            LOG_INFO("notify all consumers.");

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
