#include <atomic>
#include <thread>
#include <cassert>

std::atomic<bool> x{false};
std::atomic<bool> y{false};
std::atomic<int> z{0};

void write_x_then_y()
{
    // Write x first (relaxed is fine)
    x.store(true, std::memory_order_relaxed);

    // Publish x by releasing y
    y.store(true, std::memory_order_release);
}

void read_y_then_x()
{
    // Spin until we observe the release
    while (!y.load(std::memory_order_acquire))
        ;

    // Safe to read x after acquire
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

