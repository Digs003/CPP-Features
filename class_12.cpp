#include <iostream>

class Something
{
public:
	Something() = default;
	Something(const Something&)
	{
		std::cout << "Copy constructor called\n";
	}
};

// Return Value Optimization (RVO) and Named Return Value Optimization (NRVO)
// RVO is an optimization technique that eliminates the need for a copy constructor
// when returning an object from a function. NRVO is a specific case of RVO where the
// returned object is a named variable in the function.
Something rvo()
{
	return Something{}; // calls Something() and copy constructor
}

Something nrvo()
{
	Something s{}; // calls Something()
	return s;      // calls copy constructor
}

int main()
{
	std::cout << "Initializing s1\n";
	Something s1 { rvo() }; // calls copy constructor

	std::cout << "Initializing s2\n";
	Something s2 { nrvo() }; // calls copy constructor

        return 0;
}