
#include <cstdio>
#include <string>
#include <unistd.h>
#include <stdlib.h>

#include "thread_pool.h"

using namespace std;


class TestThread : public Thread
{
public:
    TestThread(string name)
        : Thread(false)
        , name_(name)
    {}

    virtual void run()
    {
        for (int i = 0; i < 10; ++i)
        {
            sleep(1);
            printf("%s thread loop: %d\n", name_.c_str(), rand() % 100);
        }
        printf("%s loop done!\n", name_.c_str());
    }

private:
    string name_;
};

int main()
{
    srand(time(NULL));

    TestThread test1("t1");
    TestThread test2("t2");
    test1.start();
    test2.start();

    for (int i = 0; i < 20; ++i) {
        sleep(1);
        printf("main loop: %d\n", i);
    }
    printf("main loop done!\n");
    
    return 0;
}
