class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id{ id }
    {
    }

    int getId() const { return m_id; }
};

// Incorrect Approach
// class Derived: public Base
// {
// public:
//     double m_cost {};

//     Derived(double cost=0.0, int id=0)
//         // does not work
//         : m_cost{ cost }
//         , m_id{ id }
//     {
//     }

//     double getCost() const { return m_cost; }
// };


//Works in this case but not when m_id is a const or reference member
// class Derived: public Base
// {
// public:
//     double m_cost {};

//     Derived(double cost=0.0, int id=0)
//         : m_cost{ cost }
//     {
//         m_id = id;
//     }

//     double getCost() const { return m_cost; }
// };


//Correct Approach
class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0, int id=0)
        : Base{ id } // Call Base(int) constructor with value id!
        , m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};