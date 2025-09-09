
// int main()
// {
// 	Base* b{ getObject(true) };

// 	Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer

// 	if (d) // make sure d is non-null
// 		std::cout << "The name of the Derived is: " << d->getName() << '\n';

// 	delete b;

// 	return 0;
// }