
#include <unistd.h>
#include <stdlib.h>

#include "thread_pool.h"

using namespace std;

class TestClosure : public Closure
{
public:
    TestClosure(int id)
        : id_(id)
    {  }

    void run() override
    {
        sleep(1);
        LOG_INFO("job % done!\n", id_);
    }

private:
    int id_;
};


int main()
{
    ThreadPool tp(3);

    // resource leak is on purpose
    for (int i = 0; i < 3; ++i) {
        Closure* c = new TestClosure(i);
        tp.add_job(c);
    }

    tp.start_all_workers();

    LOG_INFO("main begin sleep 5");
    sleep(5);
    LOG_INFO("main end sleep 5");

    // resource leak is on purpose
    for (int i = 10; i < 20; ++i) {
        Closure* c = new TestClosure(i);
        tp.add_job(c);
    }
    
    return 0;
}
