#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include <chrono>

// Shared data (non-atomic)
std::vector<int> queue_data;

// Atomic counter used as synchronization gateway
std::atomic<int> count{0};

// Dummy helper functions
void process(int value)
{
    // Simulate processing
    std::cout << "Processed value: " << value << std::endl;
}

void wait_for_more_items()
{
    // Simulate waiting
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

// Producer thread
void populate_queue()
{
    unsigned const number_of_items = 20;

    queue_data.clear();
    for (unsigned i = 0; i < number_of_items; ++i)
    {
        queue_data.push_back(i);
    }

    // Publish the data
    count.store(number_of_items, std::memory_order_release);
}

// Consumer threads
void consume_queue_items()
{
    while (true)
    {
        int item_index =
            count.fetch_sub(1, std::memory_order_acquire);

        if (item_index <= 0)
        {
            wait_for_more_items();
            continue;
        }

        // Safe because of release sequence
        process(queue_data[item_index - 1]);
    }
}

int main()
{
    std::thread producer(populate_queue);
    std::thread consumer1(consume_queue_items);
    std::thread consumer2(consume_queue_items);

    producer.join();
    consumer1.join();
    consumer2.join();
}

