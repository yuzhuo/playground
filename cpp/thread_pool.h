
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "log.h"

#include <vector>

#include "thread.h"
#include "closure.h"
#include "pc_queue.h"

class WorkerThread : public JoinableThread
{
    typedef void (*work_t)(void *);
public:
    WorkerThread(work_t w, void *args)
        : work_(w)
        , args_(args)
    {  }

    virtual void run() override
    {
        work_(args_);
    }

private:
    work_t work_;
    void* args_;
};

class ThreadPool
{
public:
    ThreadPool(int size)
        : pool_size_(size)
        , pc_queue_(-1)
    {
        begin_job();
        for (int i = 0; i < size; ++i) {
            pool_.push_back(new WorkerThread(&ThreadPool::do_work, this));
        }
    }

    ~ThreadPool()
    {
        end_job();
        for (int i = 0; i < pool_size_; ++i) {
            pool_[i]->join();
        }

        for (int i = 0; i < pool_size_; ++i) {
            delete pool_[i];
        }
    }

    void start_all_workers()
    {
        for (int i = 0; i < pool_size_; ++i) {
            pool_[i]->start();
        }
    }

    void add_job(Closure *c)
    {
        pc_queue_.produce(c);
    }

private:
    static void do_work(void *args)
    {
        ThreadPool *tp = static_cast<ThreadPool*>(args);
        while (tp->pc_queue_.has_work_todo()) {
            Closure* c = nullptr;
            tp->pc_queue_.consume(c);
            c->run();
        }
        LOG_INFO("a consumer exit");
    }

    void begin_job()
    {
        pc_queue_.add_a_producer();
    }

    void end_job()
    {
        pc_queue_.remove_a_producer();
        LOG_INFO("a producer exit.");
    }

private:
    std::vector<JoinableThread*> pool_;
    ProducerConsumerQueue<Closure*> pc_queue_;
    int pool_size_;
};

#endif /* __THREAD_POOL_H__ */
