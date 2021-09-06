/* *********************************************
* This example gives some sort examples in c++.
********************************************* */

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <list>

class Duck
{
    private:

    std::string m_name;
    int m_weight;

    public:

    Duck(const std::string& name, const int weight) : m_name(name), m_weight(weight)
    {
    }

    int getWeight() const
    {
        return m_weight;
    }

    operator std::string() const
    {
        return m_name + " weights " + std::to_string(m_weight);
    }

    friend bool operator<(const Duck& l, const Duck& r)
    {
        return (l.getWeight() < r.getWeight());
    }
};

std::ostream& operator<<(std::ostream& out, const Duck& duck);
std::ostream& operator<<(std::ostream& out, const Duck& duck)
{
    return out << std::string(duck);
}

static void display(std::array<std::shared_ptr<Duck>, 6> ducksArray)
{
    for (uint i = 0; i < ducksArray.size(); i++)
    {
        std::cout << *ducksArray[i] << std::endl;
    }
}

int main()
{
    std::shared_ptr<Duck> a = std::make_shared<Duck>("Daffy", 8);
    std::shared_ptr<Duck> b = std::make_shared<Duck>("Dewey", 2);
    std::shared_ptr<Duck> c = std::make_shared<Duck>("Howard", 7);
    std::shared_ptr<Duck> d = std::make_shared<Duck>("Louis", 2);
    std::shared_ptr<Duck> e = std::make_shared<Duck>("Donald", 10);
    std::shared_ptr<Duck> f = std::make_shared<Duck>("Huey", 2);

    std::array<std::shared_ptr<Duck>, 6> ducks{a, b, c, d, e, f};

    std::cout << "Before sorting array: " << std::endl;
    display(ducks);

    //using a lambda expression
    std::sort(ducks.begin(), ducks.end(), [](std::shared_ptr<Duck> left, std::shared_ptr<Duck> right){
      return left->getWeight() < right->getWeight(); 
    });

    std::cout << std::endl;
    std::cout << "After sorting array: " << std::endl;
    display(ducks);

    std::list<Duck> duckList {*a, *b, *c, *d, *e, *f};


    auto print = [&] () {
        for (Duck i : duckList)
            std::cout << i << std::endl;
    };

    std::cout << std::endl;
    std::cout << "Before sorting List: " << std::endl;
    print();

    //using the overloaded compare<
    duckList.sort();

    std::cout << std::endl;
    std::cout << "After sorting List: " << std::endl;
    print();
}