/* *********************************************
* This example implements the SINGLETON
* design pattern. This pattern ensures a class
* only has one instance and provide a global point
* of access to it.
********************************************* */

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <thread>

// Thread safe solution with lazy initialization and use of mutex
// - Resources are going to be allocated only when needed
// - Use of mutex decrease performance

class ChocolateBoiler
{
    private:

    static ChocolateBoiler* m_uniqueInstance;
    static uint m_counter;
    static std::mutex m_singletonResourcesMutex;

    bool m_empty;
    bool m_boiled;
    std::shared_ptr<std::mutex> m_businessLogicResourcesMutex = std::make_shared<std::mutex>();

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
        const std::lock_guard<std::mutex> lock(m_singletonResourcesMutex);

        if(!m_uniqueInstance)
        {
            m_uniqueInstance = new ChocolateBoiler();
        }

        increaseCounter();

        return m_uniqueInstance;
    }

    static void releaseInstance()
    {
        const std::lock_guard<std::mutex> lock(m_singletonResourcesMutex);
        
		decreaseCounter();	

		if((m_counter == 0) && (m_uniqueInstance != nullptr))
		{
			delete m_uniqueInstance;
			m_uniqueInstance = nullptr;						
		}
    }

    void fill()
    {
        const std::lock_guard<std::mutex> lock(*m_businessLogicResourcesMutex);
        if(isEmpty())
        {
            m_empty = false;
            m_boiled = false;
            std::cout << "Fill the boiler with a milk/chocolate mixture" << std::endl;
        }
    }

    void boil()
    {
        const std::lock_guard<std::mutex> lock(*m_businessLogicResourcesMutex);
        if(!isEmpty() && !isBoiled())
        {
            std::cout << "Bring the contents to a boil" << std::endl;
            m_boiled = true;
        }
    }

    void drain()
    {
        const std::lock_guard<std::mutex> lock(*m_businessLogicResourcesMutex);
        if(!isEmpty() && isBoiled())
        {
            std::cout << "Drain the boiled milk and chocolate" << std::endl;
            m_empty = true;
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
// Declare ChocolateBoiler::m_resourcesMutex to prevent link errors
std::mutex ChocolateBoiler::m_singletonResourcesMutex;
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
    // not doing it can lead to multiple times creation-deletion of a singleton instance
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