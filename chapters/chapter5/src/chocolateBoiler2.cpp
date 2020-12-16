/* *********************************************
* This example implements the SINGLETON
* design pattern. This pattern ensures a class
* only has one instance and provide a global point
* of access to it.
********************************************* */

#include <iostream>
#include <string>
#include <thread>

// Thread safe solution with eagerly initialization
// - Resources are going to be allocated at startup
// - Prefered solution when performance is a priority

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

// Create an instance of ChocolateBoiler at startup and initialize m_uniqueInstance with it.
ChocolateBoiler* ChocolateBoiler::m_uniqueInstance = new ChocolateBoiler();
// Initialize m_counter to 0. 
uint ChocolateBoiler::m_counter = 0;

void process();

void process()
{
    ChocolateBoiler* chocolateBoiler = ChocolateBoiler::getInstance();
    chocolateBoiler->fill();
    chocolateBoiler->boil();
    chocolateBoiler->drain();
    chocolateBoiler->releaseInstance();
}

int main(void)
{
    /* ********************************************* 
    * Usage example of threadsafe using mutex 
    * singleton class 
    ********************************************* */
    
    // create the instance of ChocolateBoiler
    // not doing it can cause segmentation fault when the Singleton Instance is deleted as it will not be created again
    ChocolateBoiler* controlInstance = ChocolateBoiler::getInstance();

    std::thread process1(process);
    std::thread process2(process);
    std::thread process3(process);
    std::thread process4(process);
    std::thread process5(process);
    std::thread process6(process);

    process1.join();
    process2.join();
    process3.join();
    process4.join();
    process5.join();
    process6.join();

    // delete the instance of ChocolateBoiler
    controlInstance->releaseInstance();
}