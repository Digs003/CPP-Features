#include <string>
#include <string_view>

class Person
{
public:
    std::string m_name;
    int m_age;

    Person(std::string_view name = "", int age = 0)
        :m_name(name), m_age(age)
    {
    }
    const std::string& getName() const
    {
        return m_name;
    }
    int getAge() const 
    {
        return m_age;
    }
};

class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(std::string_view name = "", int age = 0,double battingAverage = 0.0, int homeRuns = 0)
        : Person{ name,age }, m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};


