/* *********************************************
* This example implements the SINGLETON
* design pattern. This pattern ensures a class
* only has one instance and provide a global point
* of access to it.
********************************************* */

#include <iostream>
#include <string>

// Thread unsafe solution with lazy initialization
// - Resources are going to be allocated only when needed
// - Useful when running in only one thread

class ChocolateBoiler
{
    private:

    static ChocolateBoiler* m_uniqueInstance;
    static uint m_counter;

    bool m_empty;
    bool m_boiled;

    // make constructor inaccessible through new
    ChocolateBoiler() : m_empty(true), m_boiled(false)
    {
        std::cout << "instance created" << std::endl;
    }

    // make destructor inaccessible through delete
    ~ChocolateBoiler()
    {
        std::cout << "instance deleted" << std::endl;
    }

    static void increaseCounter(){
		++m_counter;
	}
	static void decreaseCounter(){
		--m_counter;
	}
   
    public:

    static ChocolateBoiler* getInstance()
    {
        if(!m_uniqueInstance)
        {
            m_uniqueInstance = new ChocolateBoiler();
        }

        increaseCounter();

        return m_uniqueInstance;
    }

    static void releaseInstance()
    {
		decreaseCounter();	

		if((m_counter == 0) && (m_uniqueInstance != nullptr))
		{
			delete m_uniqueInstance;
			m_uniqueInstance = nullptr;						
		}
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
ChocolateBoiler* ChocolateBoiler::m_uniqueInstance = nullptr;
// Initialize m_counter to 0. 
uint ChocolateBoiler::m_counter = 0;

int main(void)
{
    /* ********************************************* 
    * Usage example of thread unsafe singleton class 
    ********************************************* */

    ChocolateBoiler* chocolateBoiler_1 = ChocolateBoiler::getInstance();
    // or ChocolateBoiler* chocolateBoiler_1 = chocolateBoiler->getInstance();
    ChocolateBoiler* chocolateBoiler_2 = ChocolateBoiler::getInstance();

    chocolateBoiler_1->fill();
    chocolateBoiler_1->boil();
    chocolateBoiler_1->drain();
    std::cout << std::endl;

    chocolateBoiler_2->fill();
    chocolateBoiler_2->boil();

    // pointers to singleton have to be released otherwise there will be a memory leak
    // release object when not needed anymore
    chocolateBoiler_1->releaseInstance();

    chocolateBoiler_2->drain();

    // pointers to singleton have to be released otherwise there will be a memory leak
    chocolateBoiler_2->releaseInstance();
}