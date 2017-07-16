
#include <pthread.h>
#include <vector>
#include <iostream>
using namespace std;


class Thread
{
public:
    Thread(bool joinable) : joinable_(joinable) {}
    virtual ~Thread() {}

    void start();

    pthread_t thread_id()
    {
        return tid_;
    }

public:
    Thread(const Thread& rhs) = delete;
    Thread& operator=(const Thread& rhs) = delete;

protected:
    virtual void run() = 0;

    static void* ThreadRunner(void *args)
    {
        Thread *t = static_cast<Thread*>(args);
        t->run();
        return nullptr;
    }

protected:
    bool joinable_;
    pthread_t tid_;
};


class WorkerThread : public Thread
{
    typedef void* (*job_t)(void*);
public:
    WorkerThread(job_t job, void *args)
        : Thread(true)
        , job_(job)
        , args_(args)
    {}

    void join();

    virtual void run()
    {
        job_(args_);
    }

private:
    job_t job_;
    void* args_;
};

static void *count_down(void *args)
{
    for (int i = 0; i < 10; ++i) {
        cout << i << endl;
    }
    return nullptr;
}

class ThreadPool
{
public:
    ThreadPool(int size)
        : pool_size_(size)
    {
        for (int i = 0; i < size; ++i) {
            pool_.push_back(new WorkerThread(count_down, nullptr));
        }
    }

    ~ThreadPool()
    {
        for (int i = 0; i < pool_size_; ++i) {
            //pool_[i]->join();
        }

        for (int i = 0; i < pool_size_; ++i) {
            delete pool_[i];
        }
    }

    void start_all_workers();

private:
    std::vector<Thread*> pool_;
    int pool_size_;
};
