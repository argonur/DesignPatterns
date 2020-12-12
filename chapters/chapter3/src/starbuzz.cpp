/* *********************************************
* This example implements the DECORATOR
* design pattern. The objective is to attach additional
* responsabilities to an object dinamically.
* Decorators provide a flexible alternative to subclassing
* for extending functionality.
********************************************* */

#include <iostream>
#include <string>

class Beverage {
    protected:
    
        std::string m_description = "unknown beverage";

    public:

        virtual ~Beverage() = default;
        virtual std::string getDescription() {
            return m_description;
        }

        virtual double cost() = 0;

};

class CondimentDecorator : public Beverage {
    public:
        virtual ~CondimentDecorator() = default;
        virtual std::string getDescription() = 0;
};

class Espresso : public Beverage {

    public:
    
        Espresso()
        {
            m_description = "Espresso";
        }

        double cost() override {
            return 1.99;
        }
};

class HouseBlend : public Beverage {
    
    public:

        HouseBlend() {
            m_description = "House Blend Coffee";
        }

        double cost() override {
            return 0.89;
        }

};

class DarkRoast : public Beverage {

    public:

        DarkRoast() {
            m_description = "Dark Roast Coffee";
        }

        double cost() override {
            return 0.99;
        }
};

class Decaf : public Beverage {

    public:

        Decaf() {
            m_description = "Decaf Coffee";
        }

        double cost() override {
            return 1.05;
        }
};

class Mocha : public CondimentDecorator {
    private:
        Beverage* m_beverage;
    
    public:

        Mocha(const Mocha&) = default;
        Mocha& operator=(const Mocha&) = default;

        Mocha(Beverage* beverage) : m_beverage(beverage) 
        {
        
        }

        ~Mocha(){
            delete m_beverage;
        }

        std::string getDescription() override {
            return (m_beverage->getDescription() + ", Mocha");
        }

        double cost() override {
            return (0.20 + m_beverage->cost()); 
        }
};

class SteamedMilk : public CondimentDecorator {
    private:
        Beverage* m_beverage;
    
    public:

        SteamedMilk(const SteamedMilk&) = default;
        SteamedMilk& operator=(const SteamedMilk&) = default;

        SteamedMilk(Beverage* beverage) : m_beverage(beverage) 
        {
        
        }

        ~SteamedMilk() {
            delete m_beverage;
        }

        std::string getDescription() override {
            return (m_beverage->getDescription() + ", Steamed Milk");
        }

        double cost() override {
            return (0.10 + m_beverage->cost()); 
        }
};

class Soy : public CondimentDecorator {
    private:
        Beverage* m_beverage;
    
    public:

        Soy(const Soy&) = default;
        Soy& operator=(const Soy&) = default;

        Soy(Beverage* beverage) : m_beverage(beverage) 
        {
        
        }

        ~Soy() {
            delete m_beverage;
        }

        std::string getDescription() override {
            return (m_beverage->getDescription() + ", Soy");
        }

        double cost() override {
            return (0.15 + m_beverage->cost()); 
        }
};

class Whip : public CondimentDecorator {
    private:
        Beverage* m_beverage;
    
    public:

        Whip(const Whip&) = default;
        Whip& operator=(const Whip&) = default;

        Whip(Beverage* beverage) : m_beverage(beverage) 
        {
        
        }

        ~Whip() {
            delete m_beverage;
        }

        std::string getDescription() override {
            return (m_beverage->getDescription() + ", Whip");
        }

        double cost() override {
            return (0.10 + m_beverage->cost()); 
        }
};

int main(void)
{
    std::cout << "chapter 3 - decorator" << std::endl;

    Beverage* beverage = new Espresso();
    std::cout << beverage->getDescription() << ", $"<<  beverage->cost() << std::endl;

    Beverage* beverage2 = new DarkRoast();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);
    std::cout << beverage2->getDescription() << ", $"<<  beverage2->cost() << std::endl;

    Beverage* beverage3 = new HouseBlend();
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    std::cout << beverage3->getDescription() << ", $"<<  beverage3->cost() << std::endl;

    delete beverage;
    delete beverage2;
    delete beverage3;
}