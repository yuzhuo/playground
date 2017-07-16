

#include <iostream>

#include "mutex.h"
#include "thread_pool.h"
using namespace std;

int x = 0;
int y = 0;

MutexLock mutex;
Condition cond(mutex);

class TestThread2 : public Thread
{
public:
    TestThread2()
        :Thread(true)
    {  }

    virtual void run()
    {
        MutexLockGuard slg(mutex);
        cout << "thread2 begin to work" << endl;
        for (int i = 0; i < 1000 * 1000; ++i) {
            x += 1;
        }
        y = 1;
        cond.notify_all();
        cout << "thread2 end work" << endl;
    }

    void join()
    {
        pthread_join(tid_, nullptr);
    }
};

class TestThread1 : public Thread
{
public:
    TestThread1()
        :Thread(true)
    {  }

    virtual void run()
    {
        MutexLockGuard mlg(mutex);
        cout << "thread1 try to read x" << endl;
        while (1 != y) {
            cout << "wake up" << endl;
            for (int i = 0; i < 1000 * 1000; ++i) {
                int x = 10 * 10;
            }
            cout << "thread1 wait" << endl;
            cond.wait();
        }
            
        cout << "x: " << x << endl;
    }

    void join()
    {
        pthread_join(tid_, NULL);
    }
};

int main()
{
    TestThread1 t1;
    TestThread2 t2;

    t2.start();
    t1.start();

    cout << "main thread begin join" << endl;
    t1.join();
    t2.join();
    cout << "main thread end join" << endl;

    return 0;
}
