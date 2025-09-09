#include <iostream>
#include <functional>

void myInvoke(const std::function<void()>& fn)
{
    fn();
}

int main()
{
    int i{ 0 };

    // Increments and prints its local copy of @i.
    auto count{ [i]() mutable {
      std::cout << ++i << '\n';
    } };

    myInvoke(count);
    myInvoke(count);
    myInvoke(count);

    return 0;
}
//When we call myInvoke(count), the compiler will see that count (which has a lambda type) doesn’t match the type of the reference parameter type (std::function<void()>).
// It will convert the lambda into a temporary std::function so that the reference parameter can bind to it and this will make a copy of the lambda.
// Thus, our call to fn() is actually being executed on the copy of our lambda that exists as part of the temporary std::function, not the actual lambda.

// Correct approach:

#include <iostream>
#include <functional>

void myInvoke(const std::function<void()>& fn)
{
    fn();
}

int main()
{
    int i{ 0 };

    // Increments and prints its local copy of @i.
    std::function count{ [i]() mutable { // lambda object stored in a std::function
      std::cout << ++i << '\n';
    } };

    myInvoke(count); // doesn't create copy when called
    myInvoke(count); // doesn't create copy when called
    myInvoke(count); // doesn't create copy when called

    return 0;
}