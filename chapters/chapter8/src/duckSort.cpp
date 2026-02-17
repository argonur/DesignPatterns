/* *********************************************
* This example gives some sort examples in c++.
********************************************* */

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <list>
#include <array>

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

// Versión con unique_ptr - recibimos por referencia para no consumir los unique_ptr
static void display(const std::array<std::unique_ptr<Duck>, 6>& ducksArray)
{
    for (size_t i = 0; i < ducksArray.size(); i++)
    {
        if (ducksArray[i]) {  // Verificamos que no sea nullptr
            std::cout << *ducksArray[i] << std::endl;
        }
    }
}

int main()
{
    // Creamos los unique_ptr directamente
    std::array<std::unique_ptr<Duck>, 6> ducks = {
        std::make_unique<Duck>("Daffy", 8),
        std::make_unique<Duck>("Dewey", 2),
        std::make_unique<Duck>("Howard", 7),
        std::make_unique<Duck>("Louis", 2),
        std::make_unique<Duck>("Donald", 10),
        std::make_unique<Duck>("Huey", 2)
    };

    std::cout << "Before sorting array: " << std::endl;
    display(ducks);

    //using a lambda expression
    std::sort(ducks.begin(), ducks.end(), [](const std::unique_ptr<Duck>& left, const std::unique_ptr<Duck>& right){
      return left->getWeight() < right->getWeight(); 
    });

    std::cout << std::endl;
    std::cout << "After sorting array: " << std::endl;
    display(ducks);

    std::list<Duck> duckList {*ducks[0], *ducks[1], *ducks[2], *ducks[3], *ducks[4], *ducks[5]};

    auto print = [&] () {
        for (const Duck& i : duckList)
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