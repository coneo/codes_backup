#include "../single_producer_and_single_consumer_lock_free_circular_queue.h"
#include "../circular_queue.h"

#include "test.h"

#include <thread>
#include <mutex>


using namespace water;

const int64_t N = 10 * 1000 * 1000;
const int64_t queueSizePow = 16;

void singleThread()
{
    LockFreeCircularQueue<int64_t> queue(5);

    for(int64_t i = 0; i < N; ++ i)
        queue.push(i);

    int64_t sum = 0;
    int64_t item = 0;

    while(queue.pop(&item))
        sum += item;

    cout << sum << endl;
}

void singleProducerAndSingleConsumerMutexVersion()
{
    CircularQueue<int64_t> queue(1 << queueSizePow);

    std::mutex mutex;

    auto producerDo = [&]()
    {
        int64_t i = 0; 
        while(i < N)
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                if(queue.full())
                    continue;

                queue.push(i);
            }
            ++i;
        }
    };

    auto consumerDo = [&]()
    {
        int64_t sum = 0;
        int64_t count = 0;
        while (count < N)
        {
            int64_t item = 0;
            {
                std::unique_lock<std::mutex> lock(mutex);
                if(queue.empty())
                    continue;

                item = queue.get();
                queue.pop();
            }
            ++count;
            sum += item;
        }

        cout << sum << endl;
    };

    std::thread consumer(consumerDo);
    std::thread procuder(producerDo);

    procuder.join();
    consumer.join();
}

void singleProducerAndSingleConsumer()
{
    LockFreeCircularQueue<int64_t> queue(queueSizePow); //容量远小于数据量的queue
    auto producerDo = [&]()
    {
        int64_t i = 0;
        while(i < N)
        {
            while(!queue.push(i))
            {
            }
            ++i;
        }
    };

    auto consumerDo = [&]()
    {
        int64_t sum = 0;
        int64_t count = 0;
        while (count < N)
        {
            int64_t item = 0;
            if(!queue.pop(&item))
            {
               // std::this_thread::yield();
                continue;
            }
            ++count;
            sum += item;
        }

        cout << sum << endl;
    };

    std::thread consumer(consumerDo);
    std::thread procuder(producerDo);

    procuder.join();
    consumer.join();
}

void multiProducerAndMultiConsumer()
{
    LockFreeCircularQueue<int64_t> queue(10);
    auto producerDo = [&]()
    {
        for(int64_t i = 0; i < N; ++i)
        {
            while(!queue.push(i))
            {//已满
 //               std::this_thread::yield(); 
            }
        }
    };

    std::atomic<int64_t> count(0);
    std::atomic<int64_t> sum(0);
    auto consumerDo = [&]()
    {
        while (count < N * 5)
        {
            int64_t item = 0;
            while(queue.pop(&item))
            {
                count.fetch_add(1, std::memory_order_relaxed);
                sum.fetch_add(item, std::memory_order_relaxed);
            }

//            std::this_thread::yield();
        }

    };

    std::vector<std::thread> consumers(5);
    std::vector<std::thread> producers(5);
    for(int i = 0; i < 5; ++i)
    {
        producers[i] = std::thread(consumerDo);
        consumers[i] = std::thread(producerDo);
    }

    cout << "wait for end " << endl;

    for(int i = 0; i < 5; ++i)
    {
        producers[i].join();
        consumers[i].join();
    }

    cout << sum << endl;
}

int main()
{
    int64_t sum = 0;
    for(int64_t i = 0; i < N; ++i)
        sum += i;

    singleThread();
    performance(singleProducerAndSingleConsumer, 1);
    performance(singleProducerAndSingleConsumerMutexVersion, 1);
//    multiProducerAndMultiConsumer();
    return 0;
}


