
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "thread.h"

int count = 0;

class TestThread : public JoinableThread
{
public:
    TestThread() {
        count = 0;
    }

    void start(bool b)
    {
        pthread_attr_t attr;

        pthread_attr_init(&attr);

        //if (b) {
            //cpu_set_t cpu_info;
            //CPU_ZERO(&cpu_info);
            //CPU_SET(0, &cpu_info);
            //pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_info);
            //printf("bind to cpu 0\n");
        //} else {
            //cpu_set_t cpu_info;
            //CPU_ZERO(&cpu_info);
            //CPU_SET(1, &cpu_info);
            //pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_info);
            //printf("bind to cpu 1\n");
        //}
        
        int detachstate = joinable_ ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED;
        pthread_attr_setdetachstate(&attr, detachstate);
        pthread_create(&tid_, &attr, &Thread::thread_runner, this);

        pthread_attr_destroy(&attr);
    }

    void print_affinity_info()
    {
        cpu_set_t cpuset;
        int s = pthread_getaffinity_np(thread_id(), sizeof(cpu_set_t), &cpuset);
        printf("Set returned by pthread_getaffinity_np() contained:\n");
        for (int j = 0; j < 2; j++)
            if (CPU_ISSET(j, &cpuset))
                printf("    CPU %d\n", j);
    }

    virtual void run() override
    {
        struct timeval end;
        gettimeofday(&end, NULL);
        printf("thread: %u begin, %d %d\n", thread_id(), end.tv_sec, end.tv_usec);
        end.tv_sec += 1;
        struct timeval now;
        //while (1) {
        while (count < 458157850) {
            int sum = 1;
            sum += 10 * 10;

            count += 1;
            /*gettimeofday(&now, NULL);*/
            /*if (now.tv_sec >= end.tv_sec && now.tv_usec >= end.tv_usec)*/
                /*break;*/
        }
        gettimeofday(&now, NULL);
        printf("thread: %u, %d %d, sleep\n", thread_id(), now.tv_sec, now.tv_usec);
        sleep(1);
    }

private:
    int count;
};


/*void handler(int sigval)*/
/*{*/
    /*struct timeval now;*/
    /*gettimeofday(&now, NULL);*/
    /*printf("count:%d\n", count);*/
    /*printf("%d %d\n", now.tv_sec, now.tv_usec);*/
    /*printf("sleep 1 second.\n");*/
    /*sleep(1);*/
    /*exit(1);*/
/*}*/



int main()
{
    /*signal(SIGALRM, handler);*/
    /*alarm(1);*/
    printf("cpu count: %d\n", get_cpu_count());
    printf("program begins.\n");
    TestThread tt1;
    TestThread tt2;
    TestThread tt3;
    TestThread tt4;

    tt1.start(true);
    tt2.start(false);

    //tt1.print_affinity_info();
    //tt2.print_affinity_info();

    tt3.start(true);
    tt4.start(false);
    tt1.join();
    tt2.join();
    tt3.join();
    tt4.join();

    return 0;
}
