/* *********************************************
* This example implements the ADAPTER
* design pattern, which converts the interface of a class
* into another interface the clients expect. Adapter lets
* classes work together that couldn't otherwise because
* of incompatible interfaces.
********************************************* */

#include <iostream>

class Duck
{
    public:
    virtual ~Duck() = default;
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class MallardDuck : public Duck
{
    public:

    void quack() override
    {
        std::cout << "Quack" << std::endl;
    }

    void fly() override
    {
        std::cout << "I'm flying" << std::endl;
    }
};

class Turkey
{
    public:
    virtual ~Turkey() = default;
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

class WildTurkey : public Turkey
{
    public:

    void gobble() override
    {
        std::cout << "Gobble gobble" << std::endl;
    }

    void fly() override
    {
        std::cout << "I'm flying a short distance" << std::endl;
    }
};

class TurkeyAdapter : public Duck
{
    private:

    Turkey* m_turkey;

    public:

    TurkeyAdapter(Turkey* turkey) : m_turkey(turkey)
    {
        
    }

    ~TurkeyAdapter()
    {

    }

    TurkeyAdapter(const TurkeyAdapter&) = default;

    TurkeyAdapter& operator=(const TurkeyAdapter&) = default;

    void quack() override
    {
        m_turkey->gobble();
    }

    void fly() override
    {
        for (uint i = 0; i < 5 ; i++)
        {
            m_turkey->fly();
        }
    }
};

void testDuck(Duck* duck);
void testDuck(Duck* duck)
{
    duck->quack();
    duck->fly();
}

int main()
{
    MallardDuck* duck = new MallardDuck();
    WildTurkey* turkey = new WildTurkey();
    Duck* turkeyAdapter = new TurkeyAdapter(turkey);

    std::cout << "The Turkey says..." << std::endl;
    turkey->gobble();
    turkey->fly();

    std::cout << "The Duck says..." << std::endl;
    testDuck(duck);

    std::cout << "The TurkeyAdapter says..." << std::endl;
    testDuck(turkeyAdapter);


    delete duck;
    delete turkey;
    delete turkeyAdapter;
}