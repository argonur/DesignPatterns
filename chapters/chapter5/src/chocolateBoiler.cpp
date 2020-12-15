/* *********************************************
* This example implements the SINGLETON
* design pattern. This pattern ensures a class
* only has one instance and provide a global point
* of access to it.
********************************************* */

#include <iostream>
#include <string>

class ChocolateBoiler
{
    private:

    static ChocolateBoiler* m_uniqueInstance;

    bool m_empty;
    bool m_boiled;


    ChocolateBoiler() : m_empty(true), m_boiled(false)
    {

    }

    public:

    static ChocolateBoiler* getInstance()
    {
        if(!m_uniqueInstance)
        {
            m_uniqueInstance = new ChocolateBoiler();
        }
        return m_uniqueInstance;
    }

    void fill()
    {
        if(isEmpty())
        {
            m_empty = false;
            m_boiled = false;
            std::cout << "Fill the boiler with a milk/chocolate mixture" << std::endl;
        }
    }

    void drain()
    {
        if(!isEmpty() && isBoiled())
        {
            std::cout << "Drain the boiled milk and chocolate" << std::endl;
            m_empty = true;
        }
    }

    void boil()
    {
        if(!isEmpty() && !isBoiled())
        {
            std::cout << "Bring the contents to a boil" << std::endl;
            m_boiled = true;
        }
    }

    bool isEmpty()
    {
        return m_empty;
    }

    bool isBoiled()
    {
        return m_boiled;
    }
};

// Initialize m_uniqueInstance to nullptr. 
// If not initialized there is a link error!
ChocolateBoiler* ChocolateBoiler::m_uniqueInstance = nullptr;

int main(void)
{
    ChocolateBoiler* chocolateBoiler = ChocolateBoiler::getInstance();
    // or ChocolateBoiler* chocolateBoiler = chocolateBoiler->getInstance();
    chocolateBoiler->fill();
    chocolateBoiler->boil();
    chocolateBoiler->drain();
}