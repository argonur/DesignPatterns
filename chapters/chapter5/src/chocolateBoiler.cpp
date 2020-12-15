/* *********************************************
* This example implements the SINGLETON
* design pattern. This pattern ensures a class
* only has one instance and provide a global point
* of access to it.
********************************************* */

#include <iostream>
#include <string>

/* ****************************************************************** */

// Thread unsafe solution with lazy initialization
// - Resources are going to be allocated only when needed
// - Useful when running in only one thread

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
// If not declared there is a link error!
ChocolateBoiler* ChocolateBoiler::m_uniqueInstance = nullptr;

/* ****************************************************************** */

// Thread safe solution with eagerly initialization
// - Resources are going to be allocated at startup
// - Prefered solution when performance is a priority

class ChocolateBoiler2
{
    private:

    static ChocolateBoiler2* m_uniqueInstance;

    bool m_empty;
    bool m_boiled;


    ChocolateBoiler2() : m_empty(true), m_boiled(false)
    {

    }

    public:

    static ChocolateBoiler2* getInstance()
    {
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

// Create an instance of ChocolateBoiler2 at startup and initialize m_uniqueInstance with it.
ChocolateBoiler2* ChocolateBoiler2::m_uniqueInstance = new ChocolateBoiler2();

/* ****************************************************************** */

// Thread safe solution with lazy initialization and use of mutex
// - Resources are going to be allocated only when needed
// - Use of mutex decrease performance

#include <mutex>

class ChocolateBoiler3
{
    private:

    static ChocolateBoiler3* m_uniqueInstance;
    static std::mutex getInstanceMutex;

    bool m_empty;
    bool m_boiled;


    ChocolateBoiler3() : m_empty(true), m_boiled(false)
    {

    }

    public:

    static ChocolateBoiler3* getInstance()
    {
        const std::lock_guard<std::mutex> lock(getInstanceMutex);

        if(!m_uniqueInstance)
        {
            m_uniqueInstance = new ChocolateBoiler3();
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
ChocolateBoiler3* ChocolateBoiler3::m_uniqueInstance = nullptr;
// Declare ChocolateBoiler3::getInstanceMutex to prevent link errors
std::mutex ChocolateBoiler3::getInstanceMutex;

/* ****************************************************************** */

int main(void)
{
    ChocolateBoiler* chocolateBoiler = ChocolateBoiler::getInstance();
    // or ChocolateBoiler* chocolateBoiler = chocolateBoiler->getInstance();
    chocolateBoiler->fill();
    chocolateBoiler->boil();
    chocolateBoiler->drain();
    std::cout << std::endl;

    ChocolateBoiler2* chocolateBoiler2 = ChocolateBoiler2::getInstance();
    chocolateBoiler2->fill();
    chocolateBoiler2->boil();
    chocolateBoiler2->drain();
    std::cout << std::endl;

    ChocolateBoiler3* chocolateBoiler3 = ChocolateBoiler3::getInstance();
    chocolateBoiler3->fill();
    chocolateBoiler3->boil();
    chocolateBoiler3->drain();
    std::cout << std::endl;
}