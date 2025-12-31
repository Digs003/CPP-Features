#include <atomic>
#include <thread>
#include <cassert>
#include <string>
#include <chrono>

// Data structure published via a pointer
struct X
{
    int i;
    std::string s;
};

// Shared atomics
std::atomic<X*> p{nullptr};
std::atomic<int> a{0};

// Producer thread
void create_x()
{
    X* x = new X;
    x->i = 42;
    x->s = "hello";

    // Independent atomic write
    a.store(99, std::memory_order_relaxed);

    // Publish the pointer (release)
    p.store(x, std::memory_order_release);
}

// Consumer thread
void use_x()
{
    X* x;

    // Spin until pointer is published
    while (!(x = p.load(std::memory_order_consume)))
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    // These are DEPENDENT reads — safe with consume
    assert(x->i == 42);
    assert(x->s == "hello");

    // NOT dependent on x — NOT guaranteed by consume (theoretical)
    // Works in practice only because consume == acquire today
    assert(a.load(std::memory_order_relaxed) == 99);
}

int main()
{
    std::thread t1(create_x);
    std::thread t2(use_x);

    t1.join();
    t2.join();
}

