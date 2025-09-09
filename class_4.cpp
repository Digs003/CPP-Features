#include <iostream>

class Foo
{
private:
    int m_x { 0 };
    int& m_y;

public:
    Foo(int x, int& y): m_y(y) // correct: this is an initialization list
    {
        m_x = x; // incorrect: this is an assignment, not an initialization
        m_y = 5; // incorrect: this is an assignment, not an initialization
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    int y = 7;
    const Foo foo { 6, y };
    foo.print();

    return 0;
}