#include <atomic>
#include <thread>
#include <cassert>

// Shared atomics
std::atomic<bool> x{false};
std::atomic<bool> y{false};
std::atomic<int>  z{0};

void write_x_then_y()
{
    // Write x (relaxed)
    x.store(true, std::memory_order_relaxed);

    // Publish prior writes
    std::atomic_thread_fence(std::memory_order_release);

    // Signal availability
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
    // Spin until y is set
    while (!y.load(std::memory_order_relaxed))
        ;

    // Observe published writes
    std::atomic_thread_fence(std::memory_order_acquire);

    // Safe to read x after acquire fence
    if (x.load(std::memory_order_relaxed))
        ++z;
}

int main()
{
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);

    a.join();
    b.join();

    // This assertion can NEVER fail
    assert(z.load() != 0);
}

