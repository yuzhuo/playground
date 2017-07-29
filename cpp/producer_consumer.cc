
#include "log.h"

#include "thread.h"
#include "pc_queue.h"

using namespace std;

class Producer : public JoinableThread
{
public:
    Producer(ProducerConsumerQueue<char>& que)
        : pc_queue_(que)
        , ch_('a')
        , id_(Producer::id_generator_)
    {
        LOG_INFO("create a producer %", id_);

        pc_queue_.add_a_producer();
        Producer::id_generator_ += 1;
    }

    virtual void run()
    {
        while (true) {
            pc_queue_.produce(ch_);
            ++ch_;

            if ('h' == ch_) {
                LOG_INFO("producer % exits.", id_);
                pc_queue_.remove_a_producer();
                pthread_exit(NULL);
            }
        }
    }

private:
    static int id_generator_;

    ProducerConsumerQueue<char>& pc_queue_;
    char ch_;
    int id_;
};
int Producer::id_generator_ = 1;

class Consumer : public JoinableThread
{
public:
    Consumer(ProducerConsumerQueue<char>& que)
        : pc_queue_(que)
        , id_(Consumer::id_generator_)
    {
        Consumer::id_generator_ += 1;
    }

    virtual void run()
    {
        while (pc_queue_.has_work_todo()) {
            char ch;
            pc_queue_.consume(ch);
        }
        LOG_INFO(" *** consumer % exits.", id_);
    }

private:
    static int id_generator_;

    ProducerConsumerQueue<char>& pc_queue_;
    int id_;
};
int Consumer::id_generator_ = 1;

int main()
{
    ProducerConsumerQueue<char> pc_queue(10);
    Producer p1(pc_queue);
    Producer p2(pc_queue);
    Producer p3(pc_queue);
    Producer p4(pc_queue);
    p1.start();
    p2.start();
    p3.start();
    p4.start();

    Consumer c1(pc_queue);
    Consumer c2(pc_queue);
    c1.start();
    c2.start();

    LOG_INFO("main before join");
    p1.join();
    p2.join();
    p3.join();
    c1.join();
    c2.join();
    LOG_INFO("main after join");

    return 0;
}


